#include "mcsat/fm/fm_plugin.h"

using namespace CVC4;
using namespace mcsat;
using namespace fm;
using namespace util;

FMPlugin::NewVariableNotify::NewVariableNotify(FMPlugin& plugin)
: INewVariableNotify(false)
, d_plugin(plugin)
{
}

void FMPlugin::NewVariableNotify::newVariable(Variable var) {
  // Register new variables
  if (d_plugin.isArithmeticVariable(var)) {
    d_plugin.newVariable(var);
  } else {
    // Register arithmetic constraints
    TNode varNode = var.getNode();
    switch (varNode.getKind()) {
      case kind::LT: 
      case kind::LEQ:
      case kind::GT:
      case kind::GEQ:
	// Arithmetic constraints
	d_plugin.newConstraint(var);
	break;
      case kind::EQUAL:
	// TODO: Only if both sides are arithmetic
	d_plugin.newConstraint(var);
	break;
      default:
	// Ignore
	break;
    }
  }
}

FMPlugin::FMPlugin(ClauseDatabase& database, const SolverTrail& trail, SolverPluginRequest& request)
: SolverPlugin(database, trail, request)
, d_newVariableNotify(*this)
, d_trailHead(trail.getSearchContext(), 0)
, d_bounds(trail.getSearchContext())
, d_fmRule(database)
{
  Debug("mcsat::fm") << "FMPlugin::FMPlugin()" << std::endl;

  // We decide values of variables and can detect conflicts
  addFeature(CAN_PROPAGATE);
  addFeature(CAN_DECIDE);

  // Types we care about
  VariableDatabase& db = *VariableDatabase::getCurrentDB();
  d_intTypeIndex = db.getTypeIndex(NodeManager::currentNM()->integerType());
  d_realTypeIndex = db.getTypeIndex(NodeManager::currentNM()->realType());

  // Add the listener
  db.addNewVariableListener(&d_newVariableNotify);
}

std::string FMPlugin::toString() const  {
  return "Fourier-Motzkin Elimination (Model-Based)";
}

void FMPlugin::newVariable(Variable var) {
  Debug("mcsat::fm") << "FMPlugin::newVariable(" << var << ")" << std::endl;
}

class var_assign_compare {
  const SolverTrail& d_trail;
public:
  var_assign_compare(const SolverTrail& trail)
  : d_trail(trail) {}

  bool operator () (const Variable& v1, const Variable& v2) {
    bool v1_hasValue = d_trail.hasValue(v1);
    bool v2_hasValue = d_trail.hasValue(v2);

    // Two unassigned literals are sorted arbitrarily
    if (!v1_hasValue && !v2_hasValue) {
      return v1 < v2;
    }

    // Unassigned variables are put to front
    if (!v1_hasValue) return true;
    if (!v2_hasValue) return false;

    // Bot are assigned, we compare by trail idnex
    return d_trail.trailIndex(v1) > d_trail.trailIndex(v2);
  }
};

void FMPlugin::newConstraint(Variable constraint) {
  Debug("mcsat::fm") << "FMPlugin::newConstraint(" << constraint << ")" << std::endl;
  Assert(!isLinearConstraint(constraint), "Already registered");

  // The linear constraint we're creating 
  LinearConstraint linearConstraint;

  // Parse the coefficients into the constraint
  bool linear = LinearConstraint::parse(Literal(constraint, false), linearConstraint);
  
  // The plugin doesn't handle non-linear constraints
  if (!linear) {
    Debug("mcsat::fm") << "FMPlugin::newConstraint(" << constraint << "): non-linear" << std::endl;
    return;
  }

  Debug("mcsat::fm") << "FMPlugin::newConstraint(" << constraint << "): " << linearConstraint << std::endl;

  // Get the variables of the constraint
  std::vector<Variable> vars;
  linearConstraint.getVariables(vars);
  Assert(vars.size() > 0);

  // Sort the variables by trail assignment index (if any)
  var_assign_compare cmp(d_trail);
  std::sort(vars.begin(), vars.end(), cmp);

  // Add the variable list to the watch manager and watch the first two constraints
  VariableListReference listRef = d_assignedWatchManager.newListToWatch(vars);
  d_assignedWatchManager.watch(vars[0], listRef);
  if (vars.size() > 1) {
    d_assignedWatchManager.watch(vars[1], listRef);
  }
  
  // Check if anything to do immediately
  if (!d_trail.hasValue(vars[0])) {
    if (vars.size() > 1 && !d_trail.hasValue(vars[1])) {

    }
  }

  // Remember the constraint
  d_constraints[constraint].swap(linearConstraint);
  // Also remember that the list reference corresponds to this constraint
  d_varlistToVar[listRef] = constraint;
}

void FMPlugin::propagate(SolverTrail::PropagationToken& out) {
  Debug("mcsat::fm") << "FMPlugin::propagate()" << std::endl;

  unsigned i = d_trailHead;
  for (unsigned i = 0; i < d_trail.size(); ++ i) {
    Variable var = d_trail[i].var;

    if (isArithmeticVariable(var)) {

      Debug("mcsat::fm") << "FMPlugin::propagate(): " << var << " assigned" << std::endl;

      // Go through all the variable lists (constraints) where we're watching var
      AssignedWatchManager::remove_iterator w = d_assignedWatchManager.begin(var);
      while (d_trail.consistent() && !w.done()) {

        // Get the current list where var appears
        VariableListReference variableListRef = *w;
        VariableList variableList = d_assignedWatchManager.get(variableListRef);
        Debug("mcsat::fm") << "FMPlugin::propagate(): watchlist  " << variableList << " assigned" << std::endl;

        // More than one vars, put the just assigned var to position [1]
        if (variableList.size() > 1 && variableList[0] == var) {
          variableList.swap(0, 1);
        }

        // Try to find a new watch
        bool watchFound = false;
        for (unsigned j = 2; j < variableList.size(); j++) {
          if (!d_trail.hasValue(variableList[j])) {
            // Put the new watch in place
            variableList.swap(1, j);
            d_assignedWatchManager.watch(variableList[1], variableListRef);
            w.next_and_remove();
            // We found a watch
            watchFound = true;
            break;
          }
        }

        Debug("mcsat::fm") << "FMPlugin::propagate(): new watch " << (watchFound ? "found" : "not found") << std::endl;

        if (!watchFound) {
          // We did not find a new watch so vars[1], ..., vars[n] are assigned, except maybe vars[0]
          if (d_trail.hasValue(variableList[0])) {
            // Even the first one is assigned, so we have a semantic propagation
          } else {
            // The first one is not assigned, so we have a new unit constraint
          }
        }
      }
    } else if (isLinearConstraint(var)) {
      // If the constraint is unit we propagate a new bound
      if (isUnitConstraint(var)) {
        processUnitConstraint(var);
      }
    }
  }

  // Remember where we stopped
  d_trailHead = i;

  // Process any conflicts
  if (d_bounds.inConflict()) {
    processConflicts();
  }
}

bool FMPlugin::isUnitConstraint(Variable constraint) {
  return true;
}

void FMPlugin::processUnitConstraint(Variable constraint) {
  Assert(isLinearConstraint(constraint));
  Assert(isUnitConstraint(constraint));

  // Get the constraint
  const LinearConstraint& c = getLinearConstraint(constraint);

  // Compute ax + sum:
  // * the sum of the linear term that evaluates
  // * the single variable that is unassigned
  // * coefficient of the variable
  Rational sum;
  Rational a;
  Variable x;

  LinearConstraint::const_iterator it = c.begin();
  LinearConstraint::const_iterator it_end = c.end();
  for (; it != it_end; ++ it) {
    Variable var = it->first;
    // Constant term
    if (var.isNull()) {
      sum += it->second;
      continue;
    }
    // Assigned variable
    if (d_trail.hasValue(var)) {
      Rational varValue = d_trail.value(var).getNode().getConst<Rational>();
      sum += it->second * varValue;
    } else {
      Assert(x.isNull());
      x = var;
      a = it->second;
    }
  }

  // The constraint kind
  Kind kind = c.getKind();
  if (d_trail.isFalse(constraint)) {
    // If the constraint is negated, negate the kind
    kind = LinearConstraint::negateKind(kind);
  }
  if (a < 0) {
    // If a is negative flip the kind
    kind = LinearConstraint::flipKind(kind);
    a = -a;
    sum = -sum;
  }

  // Do the work (assuming a > 0)
  switch (kind) {
  case kind::GT:
  case kind::GEQ:
    // (ax + sum >= 0) <=> (x >= sum/a)
    d_bounds.updateLowerBound(x, BoundInfo(sum/a, kind == kind::GT, constraint));
    break;
  case kind::LT:
  case kind::LEQ:
    // (ax + sum <= 0) <=> (x <= sum/a)
    d_bounds.updateUpperBound(x, BoundInfo(sum/a, kind == kind::LT, constraint));
    break;
  case kind::EQUAL:
    // (ax + sum == 0) <=> (x == sum/a)
    d_bounds.updateLowerBound(x, BoundInfo(sum/a, false, constraint));
    d_bounds.updateUpperBound(x, BoundInfo(sum/a, false, constraint));
    break;
  case kind::DISTINCT:
    // TODO: add to list
    break;
  default:
    Unreachable();
  }

}

void FMPlugin::processConflicts() {
  std::set<Variable> variablesInConflict;
  d_bounds.getVariablesInConflict(variablesInConflict);

  std::set<Variable>::const_iterator it = variablesInConflict.begin();
  std::set<Variable>::const_iterator it_end = variablesInConflict.end();
  for (; it != it_end; ++ it) {
    Variable var = *it;

    const BoundInfo& lowerBound = d_bounds.getLowerBoundInfo(var);
    const BoundInfo& upperBound = d_bounds.getLowerBoundInfo(var);

    Variable lowerBoundVariable = lowerBound.reason;
    Literal lowerBoundLiteral(lowerBoundVariable, d_trail.isFalse(lowerBoundVariable));

    Variable upperBoundVariable = upperBound.reason;
    Literal upperBoundLiteral(upperBoundVariable, d_trail.isFalse(upperBoundVariable));

    d_fmRule.start(lowerBoundLiteral);
    d_fmRule.resolve(var, upperBoundLiteral);
    d_fmRule.finish();

  }

}

void FMPlugin::decide(SolverTrail::DecisionToken& out) {
  Debug("mcsat::fm") << "FMPlugin::decide()" << std::endl;
}