#include "mcsat/rules/fourier_motzkin_rule.h"

using namespace CVC4;
using namespace mcsat;
using namespace rules;
using namespace fm;

FourierMotzkinRule::FourierMotzkinRule(ClauseDatabase& clauseDB, const SolverTrail& trail)
: ProofRule("mcsat::fourier_motzkin_rule", clauseDB, trail)
{
}

/** Start the resolution */
void FourierMotzkinRule::start(Literal lit) {
  d_assumptions.clear();
  d_resolvent.clear();

  d_assumptions.insert(lit);
  bool linear = LinearConstraint::parse(lit, d_resolvent);

  Debug("mcsat::fm") << "FourierMotzkinRule: starting with " << d_resolvent << std::endl;

  Assert(linear);
}

void FourierMotzkinRule::resolve(Variable var, LinearConstraint& c1, LinearConstraint& c2) {
  // We know that both are one of >, >= so coefficients with var must be opposite
  Rational c1_C = c1.getCoefficient(var);
  Rational c2_C = c2.getCoefficient(var);
  
  // There are cases where we should fixup the coefficients 
  Assert(c1_C.sgn()*c2_C.sgn() != 0);
  if (c1_C.sgn()*c2_C.sgn() > 0) {
    if (c1.getKind() == kind::EQUAL) {
      c1.flipEquality();
    } else if (c2.getKind() == kind::EQUAL) {
      c2.flipEquality();
    } else {
      Assert(false);
    }
  }

  // Compute the new resolvent
  c1.multiply(c2_C.abs());
  c1.add(c2, c1_C.abs());
}

/** Resolve with given inequality over the given variable. */
void FourierMotzkinRule::resolve(Variable var, Literal ineq) {

  LinearConstraint toResolve;
  bool linear = LinearConstraint::parse(ineq, toResolve);
  Assert(linear);

  Debug("mcsat::fm") << "FourierMotzkinRule: resolving " << toResolve << std::endl;
  resolve(var, d_resolvent, toResolve);

  // Add to assumptions
  d_assumptions.insert(ineq);

  Debug("mcsat::fm") << "FourierMotzkinRule: got " << d_resolvent << std::endl;
}

/** Finish the derivation */
CRef FourierMotzkinRule::finish(SolverTrail::PropagationToken& propToken) {
  
  LiteralVector lits;
  
  // Add the lemma assumptions => resolvent
  // (!a1 \vee !a2 \vee ... \veee !an \vee resolvent)
  std::set<Literal>::const_iterator it = d_assumptions.begin();
  std::set<Literal>::const_iterator it_end = d_assumptions.end();
  for (; it != it_end; ++ it) {
    // negation of the assumption
    lits.push_back(~(*it));
  }
  
  // Evaluate 
  unsigned evalLevel;
  bool eval = d_resolvent.evaluate(d_trail, evalLevel);
  Assert(!eval, "Must be false");

  // Propagate
  Literal resolventLiteral = d_resolvent.getLiteral();
  propToken(~resolventLiteral, evalLevel);
  
  // Add the literal
  lits.push_back(resolventLiteral);

  return commit(lits);
}

CRef FourierMotzkinRule::resolveDisequality(Variable var, Literal varL, Literal varU, Literal D, SolverTrail::PropagationToken& propToken) {

  Debug("mcsat::fm") << "FourierMotzkinRule::resolveDisequality(" << var << "):" << std::endl;

  bool linear, eval;
  unsigned evalLevel;
  d_assumptions.clear();

  LiteralVector lits;
  lits.push_back(~varL);
  lits.push_back(~varU);
  lits.push_back(~D);
  
  // A1 should be of the form var >= l
  LinearConstraint varL_constraint;
  linear = LinearConstraint::parse(varL, varL_constraint);
  Debug("mcsat::fm") << "varL: " << varL_constraint << std::endl;
  Assert(linear);
  Assert(varL_constraint.getCoefficient(var) > 0 || varL_constraint.getKind() == kind::EQUAL);
  
  // A1 should be of the for var <= u, or -var >= u in our normal form
  LinearConstraint varU_constraint;
  linear = LinearConstraint::parse(varU, varU_constraint);
  Debug("mcsat::fm") << "varU: " << varU_constraint << std::endl;
  Assert(linear);
  Assert(varU_constraint.getCoefficient(var) < 0 || varL_constraint.getKind() == kind::EQUAL);
  
  LinearConstraint c1, c2;

  // Parse the dis-equality into the constraint c1
  linear = LinearConstraint::parse(D, c1);
  Debug("mcsat::fm") << "D: " << c1 << std::endl;
  Assert(linear);
  // Split the dis-equality into c1: (x > t), c2: (x < t)
  c1.splitDisequality(var, c2);
  Debug("mcsat::fm") << "c1: " << c1 << std::endl;
  Debug("mcsat::fm") << "c2: " << c2 << std::endl;

  // Resolve A1 and c2 into A1
  resolve(var, varL_constraint, c2);
  Literal l1 = varL_constraint.getLiteral();
  lits.push_back(l1);

  // Evaluate and propagate l1
  eval = varL_constraint.evaluate(d_trail, evalLevel);
  Assert(!eval, "Must be false");
  propToken(~l1, evalLevel);

  // Resolve A2 and c1 into A2
  resolve(var, varU_constraint, c1);
  Literal l2 = varU_constraint.getLiteral();
  lits.push_back(l2);

  // Evaluate and propagate l1
  eval = varU_constraint.evaluate(d_trail, evalLevel);
  Assert(!eval, "Must be false");
  propToken(~l2, evalLevel);

  return commit(lits);
}

