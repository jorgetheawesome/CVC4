(set-logic QF_BV)
(set-info :smt-lib-version 2.0)
(set-info :category "crafted")
(set-info :status unsat)
(declare-fun v0 () (_ BitVec 16))
(declare-fun v1 () (_ BitVec 16))
(declare-fun v2 () (_ BitVec 16))
(declare-fun v3 () (_ BitVec 16))
(declare-fun v4 () (_ BitVec 16))
(declare-fun v5 () (_ BitVec 16))
(assert (and
	 (bvule v0 v1)
	 (bvule v1 v2)
	 (bvule v2 v0)
	 (bvult (_ bv4 16) v0)
	 (bvult v2 (_ bv5 16))
	 ))
(check-sat)
(exit)
