#pragma once

#include "cvc4_private.h"

#include "expr/node.h"
#include "context/cdo.h"
#include "context/cdlist.h"

#include "mcsat/cnf/tseitin_cnf_stream.h"
#include "mcsat/clause/clause_db.h"
#include "mcsat/rules/proof_rule.h"
#include "mcsat/solver_trail.h"
#include "mcsat/bcp_engine.h"
#include "mcsat/inner_class.h"

namespace CVC4 {
namespace mcsat {

class Solver {

public:

  /** Construct the solver */
  Solver(context::UserContext* userContext, context::Context* searchContext);

  /** Destructor */
  virtual ~Solver();

  /** 
   * Assert the formula to the solver. If process is false the assertion will be
   * processed only after the call to check().
   * @param assertion the assertion
   * @param process true if to be processed as soon as possible 
   */
  void addAssertion(TNode assertion, bool process);

  /** Check if the current set of assertions is satisfiable */
  bool check();

  /** Add a plugin to the trail */
  void addPlugin(std::string plugin);

private:

  /** The variable database of the solver */
  VariableDatabase d_variableDatabase;

  /** Farm for all the clauses */
  ClauseFarm d_clauseFarm;

  /** The clause database */
  ClauseDatabase& d_problemClauses;

  /** CNF transform of the solver */
  TseitinCnfStream d_cnfStream;

  /** Listener for the output of the cnf stream */
  class CnfListener : public CnfOutputListener, public InnerClass<Solver> {
    public:
      CnfListener(Solver& solver) : InnerClass(solver) {}
      void newClause(Literals& clause);
  } d_cnfStreamListener; 


  /** Main method to add a clause */ 
  void addClause(Literals& clause);
  
  /** List of problem assertions */
  std::vector<Literals> d_newClauses;
 
  /** Main solver trail */
  SolverTrail d_trail;

  /** Rule for creating input clauses */
  rules::InputClauseRule d_rule_InputClause;

  /** All the plugins */
  std::vector<SolverPlugin*> d_plugins;

  /** The requests of the plugins */
  std::vector<SolverPluginRequest*> d_pluginRequests;

  /** Process any new clauses that were asserted */
  void processNewClauses();
  
  /** Perform propagation */
  void propagate(SolverTrail::PropagationToken::Mode mode);

  /** Has there been a backtrack request */
  bool d_backtrackRequested;

  /** The level of the backtrack request */
  size_t d_backtrackLevel;

  /** The clauses to be processed on backtrack */
  std::vector<CRef> d_backtrackClauses;

  /** Will perfrom a backtrack in order to propagate/decide clause cRef at next apropriate time */
  void requestBacktrack(unsigned level, CRef cRef);
  
  friend class SolverPluginRequest;
};

}
}



