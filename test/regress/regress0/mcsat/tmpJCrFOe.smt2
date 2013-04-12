(set-logic QF_LRA)
(set-info :smt-lib-version 2.0)
(declare-fun x0 () Real)
(declare-fun x1 () Real)
(assert (or (>= (+ (* (- 2) x0) (* 3 x1) 4) 0) (not (<= (+ (* 4 x0) (* 9 x1) (- 1)) 0))))
(assert (= (+ (* 3 x0) 1) 0))
(assert (or (not (< (+ (* 6 x0) (* (- 1) x1) (- 8)) 0)) (> (+ (* (- 7) x0) (* (- 6) x1) (- 10)) 0)))
(check-sat)
(exit)
