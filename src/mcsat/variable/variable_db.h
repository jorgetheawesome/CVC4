#pragma once

#include "cvc4_private.h"

#include "util/tls.h"
#include "context/context.h"
#include "context/cdo.h"

#include "variable.h"

namespace CVC4 {
namespace mcsat {

/** Class containing all the information needed to relocate the variables. */
class VariableRelocationInfo {

  typedef std::hash_map<Variable, Variable, VariableHashFunction> relocation_map;

  /** Map from old variables to new variable */
  relocation_map d_map;

  friend class VariableDatabase;

  /** Add the map old -> new to the map */
  void add(Variable oldVar, Variable newVar);

public:

  /**
   * Clear any information.
   */
  void clear() {
    d_map.clear();
  }

  /**
   * Returns the new variable corresponding to the old variables, or null if not relocated.
   */
  Variable relocate(Variable oldVar) const;


  /**
   * Reloacte a vector of variables.
   */
  void relocate(std::vector<Variable>& variables) const;
};


/**
 * Database of variables, both Boolean and non-Boolean. The variables are preferred
 * to nodes as they provide contiguous ids for important nodes (variables and 
 * shared terms).
 */
class VariableDatabase {

public:

  /** Interface for notification of new variables */
  class INewVariableNotify {
    /** Is this listener context dependent */
    bool d_isContextDependent;

  public:

    INewVariableNotify(bool cd)
    : d_isContextDependent(cd) {}
    virtual ~INewVariableNotify() {}

    /** Is this listener context dependent */
    bool isContextDependent() const {
      return d_isContextDependent;
    }

    virtual void newVariable(Variable var) = 0;
  };

private:

  /** Vector of types */
  std::vector<TypeNode> d_variableTypes;

  /** Map from Types to type-id */
  typedef std::hash_map<TypeNode, size_t, TypeNodeHashFunction> typenode_to_id_map;
  typenode_to_id_map d_typenodeToIdMap;

  /** Nodes of the variables */
  std::vector< std::vector<Node> > d_variableNodes;

  typedef std::hash_map<TNode, Variable, TNodeHashFunction> node_to_variable_map;

  /** Map from nodes to variable id's */
  node_to_variable_map d_nodeToVariableMap;

  /** The context we're using */
  context::Context* d_context;

  /** Context dependent number of variables */
  context::CDO<size_t> d_variablesCountAtCurrentLevel;

  /** All variables in the database */
  std::vector<Variable> d_variables;

  /** Non-context-dependent notify subscribers */
  std::vector<INewVariableNotify*> d_notifySubscribers;

  /** Context dependent notify subscribers */
  std::vector<INewVariableNotify*> d_cd_notifySubscribers;

  /** Clause database we're using */
  static CVC4_THREADLOCAL(VariableDatabase*) s_current;
  
  /** Pop notifications go through this class */
  class Backtracker : public context::ContextNotifyObj {
    VariableDatabase& d_db;
  public:
    Backtracker(context::Context* context, VariableDatabase& db);
    void contextNotifyPop();
  };

  /** Backtracker for notifications context pops */
  Backtracker d_backtracker;

  /** Backtracker is a friend in order to notify listeners on backtrack */
  friend class Backtracker;

public:

  /** Constructor with the context to obey */
  VariableDatabase(context::Context* context);

  /** Check if the node has a variable */
  bool hasVariable(TNode node) const;

  /** Create a new variable or reuse an existing one */
  Variable getVariable(TNode node);

  /**
   * Add a listener for the creation of new variables. A context independent listener will only be notified
   * once when the variable is created. If the listener is context dependent, it will be notified when the
   * variable created, but it will be re-notified on every pop so that it can update it's internal state.
   *
   * @param listener the listener
   */
  void addNewVariableListener(INewVariableNotify* listener);

  /** Return the node associated with the variable */
  TNode getNode(Variable var) const {
    if (var.isNull()) return TNode::null();
    Assert(var.typeIndex() < d_variableNodes.size());
    return d_variableNodes[var.typeIndex()][var.index()];
  }

  /** Get the type of the variable */
  TypeNode getTypeNode(Variable var) const {
    if (var.isNull()) return TypeNode::null();
    return d_variableTypes[var.typeIndex()];
  }

  /** Get the index of the given type */
  size_t getTypeIndex(TypeNode type);

  /** Returns the number of variables of a given type */
  size_t size(size_t typeIndex) const;

  /**
   * Get the current clause database
   */
  static VariableDatabase* getCurrentDB() {
    return s_current;
  }

  /**
   * Set the current database.
   */
  static void setCurrentDB(VariableDatabase* current) {
    s_current = current;
  }

  /**
   * Helper class to ensure scoped variable database.
   */
  class SetCurrent {
    VariableDatabase* old;
  public:
    /** Set the given DB in the current scope. */
    SetCurrent(VariableDatabase* db) {
      old = getCurrentDB();
      setCurrentDB(db);
    }
    ~SetCurrent() {
      setCurrentDB(old);
    }
  };

  /**
   * Performs GC keeping the varsToKeep variables and filling in the relocationInfo for the user.
   */
  void performGC(const std::set<Variable>& varsToKeep, VariableRelocationInfo& relocationInfo);
};

}
}
