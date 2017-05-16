*******************process function::  main***************
--------[B0] in ::--------
(>= i 100000);
 (= _ret 0);
 exist _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 
--------[B1] in ::--------
(>= i 100000);
 exist _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 
----------[B1]-> [B0] out -------:
(>= i 100000);
 (= _ret 0);
 exist _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 
--------[B2] in ::--------
exist _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 
----------[B2]-> [B4] out -------:
exist _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 
--------[B3] in ::--------
(< i 100000);
 exist _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 
----------[B3]-> [B2] out -------:
exist _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 
--------[B4] in ::--------
exist _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 
----------[B4]-> [B3] out -------:
(< i 100000);
 exist _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 
----------[B4]-> [B1] out -------:
(>= i 100000);
 exist _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 
--------[B5] in ::--------
(>= i 100000);
 exist _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [1,9,(- i 9)),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [1,9,i),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [0,1,(- j 1)),(let ((a!1 (* (+ (div (- _i0 0) 1) 0) 9)))
  (= (select a _i0) (select b (+ a!1 1))));
 forall _i1 in [0,1,(- j 1)),exist _i0 in [1,9,100000),(= (select a _i1) (select b _i0));
 forall _i0 in [0,1,j),(let ((a!1 (* (+ (div (- _i0 0) 1) 0) 9)))
  (= (select a _i0) (select b (+ a!1 1))));
 forall _i1 in [0,1,j),exist _i0 in [1,9,100000),(= (select a _i1) (select b _i0));
 forall _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 
----------[B5]-> [B4] out -------:
(= i 1);
 (= j 0);
 exist _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 
--------[B6] in ::--------
exist _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [1,9,(- i 9)),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [1,9,i),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [0,1,(- j 1)),(let ((a!1 (* (+ (div (- _i0 0) 1) 0) 9)))
  (= (select a _i0) (select b (+ a!1 1))));
 forall _i1 in [0,1,(- j 1)),exist _i0 in [1,9,100000),(= (select a _i1) (select b _i0));
 forall _i0 in [0,1,j),(let ((a!1 (* (+ (div (- _i0 0) 1) 0) 9)))
  (= (select a _i0) (select b (+ a!1 1))));
 forall _i1 in [0,1,j),exist _i0 in [1,9,100000),(= (select a _i1) (select b _i0));
 
----------[B6]-> [B8] out -------:
exist _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [1,9,(- i 9)),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [1,9,i),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [0,1,(- j 1)),(let ((a!1 (* (+ (div (- _i0 0) 1) 0) 9)))
  (= (select a _i0) (select b (+ a!1 1))));
 forall _i1 in [0,1,(- j 1)),exist _i0 in [1,9,100000),(= (select a _i1) (select b _i0));
 forall _i0 in [0,1,j),(let ((a!1 (* (+ (div (- _i0 0) 1) 0) 9)))
  (= (select a _i0) (select b (+ a!1 1))));
 forall _i1 in [0,1,j),exist _i0 in [1,9,100000),(= (select a _i1) (select b _i0));
 
--------[B7] in ::--------
(< i 100000);
 forall _i0 in [1,9,i),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [0,1,j),(let ((a!1 (* (+ (div (- _i0 0) 1) 0) 9)))
  (= (select a _i0) (select b (+ a!1 1))));
 forall _i1 in [0,1,j),exist _i0 in [1,9,100000),(= (select a _i1) (select b _i0));
 {exist _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)))} || {(= i 1)};
 {exist _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)))} || {(= j 0)};
 {forall _i0 in [1,9,(- i 9)),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)))} || {(= i 1)};
 {forall _i0 in [1,9,(- i 9)),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)))} || {(= j 0)};
 {forall _i0 in [0,1,(- j 1)),(let ((a!1 (* (+ (div (- _i0 0) 1) 0) 9)))
  (= (select a _i0) (select b (+ a!1 1))))} || {(= i 1)};
 {forall _i0 in [0,1,(- j 1)),(let ((a!1 (* (+ (div (- _i0 0) 1) 0) 9)))
  (= (select a _i0) (select b (+ a!1 1))))} || {(= j 0)};
 {forall _i1 in [0,1,(- j 1)),exist _i0 in [1,9,100000),(= (select a _i1) (select b _i0))} || {(= i 1)};
 {forall _i1 in [0,1,(- j 1)),exist _i0 in [1,9,100000),(= (select a _i1) (select b _i0))} || {(= j 0)};
 
----------[B7]-> [B6] out -------:
exist _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [1,9,(- i 9)),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [1,9,i),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [0,1,(- j 1)),(let ((a!1 (* (+ (div (- _i0 0) 1) 0) 9)))
  (= (select a _i0) (select b (+ a!1 1))));
 forall _i1 in [0,1,(- j 1)),exist _i0 in [1,9,100000),(= (select a _i1) (select b _i0));
 forall _i0 in [0,1,j),(let ((a!1 (* (+ (div (- _i0 0) 1) 0) 9)))
  (= (select a _i0) (select b (+ a!1 1))));
 forall _i1 in [0,1,j),exist _i0 in [1,9,100000),(= (select a _i1) (select b _i0));
 
--------[B8] in ::--------
forall _i0 in [1,9,i),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [0,1,j),(let ((a!1 (* (+ (div (- _i0 0) 1) 0) 9)))
  (= (select a _i0) (select b (+ a!1 1))));
 forall _i1 in [0,1,j),exist _i0 in [1,9,100000),(= (select a _i1) (select b _i0));
 {exist _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)))} || {(= i 1)};
 {exist _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)))} || {(= j 0)};
 {forall _i0 in [1,9,(- i 9)),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)))} || {(= i 1)};
 {forall _i0 in [1,9,(- i 9)),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)))} || {(= j 0)};
 {forall _i0 in [0,1,(- j 1)),(let ((a!1 (* (+ (div (- _i0 0) 1) 0) 9)))
  (= (select a _i0) (select b (+ a!1 1))))} || {(= i 1)};
 {forall _i0 in [0,1,(- j 1)),(let ((a!1 (* (+ (div (- _i0 0) 1) 0) 9)))
  (= (select a _i0) (select b (+ a!1 1))))} || {(= j 0)};
 {forall _i1 in [0,1,(- j 1)),exist _i0 in [1,9,100000),(= (select a _i1) (select b _i0))} || {(= i 1)};
 {forall _i1 in [0,1,(- j 1)),exist _i0 in [1,9,100000),(= (select a _i1) (select b _i0))} || {(= j 0)};
 
----------[B8]-> [B7] out -------:
(< i 100000);
 forall _i0 in [1,9,i),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [0,1,j),(let ((a!1 (* (+ (div (- _i0 0) 1) 0) 9)))
  (= (select a _i0) (select b (+ a!1 1))));
 forall _i1 in [0,1,j),exist _i0 in [1,9,100000),(= (select a _i1) (select b _i0));
 {exist _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)))} || {(= i 1)};
 {exist _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)))} || {(= j 0)};
 {forall _i0 in [1,9,(- i 9)),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)))} || {(= i 1)};
 {forall _i0 in [1,9,(- i 9)),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)))} || {(= j 0)};
 {forall _i0 in [0,1,(- j 1)),(let ((a!1 (* (+ (div (- _i0 0) 1) 0) 9)))
  (= (select a _i0) (select b (+ a!1 1))))} || {(= i 1)};
 {forall _i0 in [0,1,(- j 1)),(let ((a!1 (* (+ (div (- _i0 0) 1) 0) 9)))
  (= (select a _i0) (select b (+ a!1 1))))} || {(= j 0)};
 {forall _i1 in [0,1,(- j 1)),exist _i0 in [1,9,100000),(= (select a _i1) (select b _i0))} || {(= i 1)};
 {forall _i1 in [0,1,(- j 1)),exist _i0 in [1,9,100000),(= (select a _i1) (select b _i0))} || {(= j 0)};
 
----------[B8]-> [B5] out -------:
(>= i 100000);
 exist _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [1,9,(- i 9)),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [1,9,i),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 forall _i0 in [0,1,(- j 1)),(let ((a!1 (* (+ (div (- _i0 0) 1) 0) 9)))
  (= (select a _i0) (select b (+ a!1 1))));
 forall _i1 in [0,1,(- j 1)),exist _i0 in [1,9,100000),(= (select a _i1) (select b _i0));
 forall _i0 in [0,1,j),(let ((a!1 (* (+ (div (- _i0 0) 1) 0) 9)))
  (= (select a _i0) (select b (+ a!1 1))));
 forall _i1 in [0,1,j),exist _i0 in [1,9,100000),(= (select a _i1) (select b _i0));
 forall _i0 in [1,9,100000),(let ((a!1 (select a (+ (div (- _i0 1) 9) 0))))
  (= a!1 (select b _i0)));
 
--------[B9] in ::--------

----------[B9]-> [B8] out -------:
(= i 1);
 (= j 0);
 
--------[B10] in ::--------

----------[B10]-> [B9] out -------:

