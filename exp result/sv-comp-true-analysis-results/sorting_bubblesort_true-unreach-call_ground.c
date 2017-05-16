*******************process function::  main***************
--------[B0] in ::--------
(>= i 100000);
 (= swapped 0);
 (>= y 100000);
 (>= x 100000);
 (= _ret 0);
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 
--------[B1] in ::--------
(>= i 100000);
 (= swapped 0);
 (>= y 100000);
 (>= x 100000);
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 
----------[B1]-> [B0] out -------:
(>= i 100000);
 (= swapped 0);
 (>= y 100000);
 (>= x 100000);
 (= _ret 0);
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 
--------[B2] in ::--------
(>= i 100000);
 (= swapped 0);
 (< x i);
 (< x 100000);
 (< x y);
 (>= y 100000);
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 
----------[B2]-> [B6] out -------:
(>= i 100000);
 (= swapped 0);
 (>= y 100000);
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 
--------[B3] in ::--------
(>= i 100000);
 (= swapped 0);
 (< x i);
 (< x 100000);
 (< y i);
 (< y 100000);
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 
----------[B3]-> [B4] out -------:
(>= i 100000);
 (= swapped 0);
 (< x i);
 (< x 100000);
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 
--------[B4] in ::--------
(>= i 100000);
 (= swapped 0);
 (< x i);
 (< x 100000);
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 
----------[B4]-> [B3] out -------:
(>= i 100000);
 (= swapped 0);
 (< x i);
 (< x 100000);
 (< y i);
 (< y 100000);
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 
----------[B4]-> [B2] out -------:
(>= i 100000);
 (= swapped 0);
 (< x i);
 (< x 100000);
 (< x y);
 (>= y 100000);
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 
--------[B5] in ::--------
(>= i 100000);
 (= swapped 0);
 (< x i);
 (< x 100000);
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 {(>= y 100000)} || {(= x 0)};
 
----------[B5]-> [B4] out -------:
(>= i 100000);
 (= swapped 0);
 (< x i);
 (< x 100000);
 (= y (+ x 1));
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 
--------[B6] in ::--------
(>= i 100000);
 (= swapped 0);
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 {(>= y 100000)} || {(= x 0)};
 
----------[B6]-> [B5] out -------:
(>= i 100000);
 (= swapped 0);
 (< x i);
 (< x 100000);
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 {(>= y 100000)} || {(= x 0)};
 
----------[B6]-> [B1] out -------:
(>= i 100000);
 (= swapped 0);
 (>= y 100000);
 (>= x 100000);
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 
--------[B7] in ::--------
(>= i 100000);
 (= swapped 0);
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 
----------[B7]-> [B6] out -------:
(>= i 100000);
 (= swapped 0);
 (= x 0);
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 
--------[B8] in ::--------
(>= i 100000);
 {(= swapped 1)} || {(= swapped 0)};
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {(= swapped 0)};
 {(= swapped 1)} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {(= swapped 1)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {(= swapped 1)} || {forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))};
 
----------[B8]-> [B15] out -------:
(>= i 100000);
 {(= swapped 1)} || {(= swapped 0)};
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {(= swapped 0)};
 {(= swapped 1)} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {(= swapped 1)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {(= swapped 1)} || {forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))};
 
--------[B9] in ::--------
{(= swapped 1)} || {(= swapped 0)};
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {(= swapped 0)};
 {(= swapped 1)} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {(= swapped 1)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 
----------[B9]-> [B13] out -------:
{(= swapped 1)} || {(= swapped 0)};
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {(= swapped 0)};
 {(= swapped 1)} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {(= swapped 1)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 
--------[B10] in ::--------
(<= (select a (- i 1)) (select a i));
 (< i 100000);
 {(= swapped 1)} || {(= swapped 0)};
 {(= swapped 1)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {(= swapped 1)} || {forall _i0 in [1,1,(+ i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,(+ i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,(+ i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,(+ i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 
----------[B10]-> [B9] out -------:
{(= swapped 1)} || {(= swapped 0)};
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {(= swapped 0)};
 {(= swapped 1)} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {(= swapped 1)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 
--------[B11] in ::--------
(< i 100000);
 (> (select a (- i 1)) (select a i));
 {(= swapped 1)} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {(= swapped 0)};
 {(= swapped 1)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))} || {(= i 1)};
 exist _i0 in [1,1,100000),(> (select a (- _i0 1)) (select a _i0));
 
----------[B11]-> [B10] out -------:
(< (select a (- i 1)) (select a i));
 (< t (select a i));
 (< i 100000);
 (= (select a (- i 1)) t);
 (= swapped 1);
 exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0));
 exist _i0 in [1,1,100000),(< t (select a _i0));
 exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t);
 
--------[B12] in ::--------
(< i 100000);
 {(= swapped 1)} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {(= swapped 0)};
 {(= swapped 1)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))} || {(= i 1)};
 
----------[B12]-> [B11] out -------:
(< i 100000);
 (> (select a (- i 1)) (select a i));
 {(= swapped 1)} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {(= swapped 0)};
 {(= swapped 1)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))} || {(= i 1)};
 exist _i0 in [1,1,100000),(> (select a (- _i0 1)) (select a _i0));
 
----------[B12]-> [B10] out -------:
(< i 100000);
 (<= (select a (- i 1)) (select a i));
 {(= swapped 1)} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {(= swapped 0)};
 {(= swapped 1)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 {(= swapped 1)} || {forall _i0 in [1,1,(+ i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,(+ i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,(+ i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,(+ i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 
--------[B13] in ::--------
{(= swapped 1)} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {(= swapped 0)};
 {(= swapped 1)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))} || {(= i 1)};
 
----------[B13]-> [B12] out -------:
(< i 100000);
 {(= swapped 1)} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {(= swapped 0)};
 {(= swapped 1)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))} || {(= i 1)};
 
----------[B13]-> [B8] out -------:
(>= i 100000);
 {(= swapped 1)} || {(= swapped 0)};
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {(= swapped 0)};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {(= swapped 0)};
 {(= swapped 1)} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {(= swapped 1)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {(= swapped 1)} || {forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< (select a (- _i0 1)) (select a _i0))} || {forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(< t (select a _i0))} || {forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))};
 {exist _i0 in [1,1,100000),(= (select a (- _i0 1)) t)} || {forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))};
 
--------[B14] in ::--------
(distinct swapped 0);
 (= swapped 1);
 
----------[B14]-> [B13] out -------:
(= swapped 0);
 (= i 1);
 
--------[B15] in ::--------
{(= swapped 1)} || {(= swapped 0)};
 {(= swapped 1)} || {forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0))};
 {(= swapped 1)} || {forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0))};
 {(= swapped 1)} || {forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))};
 {(>= i 100000)} || {(= swapped 1)};
 {exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0))} || {(= swapped 1)};
 
----------[B15]-> [B14] out -------:
(distinct swapped 0);
 (= swapped 1);
 
----------[B15]-> [B7] out -------:
(>= i 100000);
 (= swapped 0);
 exist _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,i),(<= (select a (- _i0 1)) (select a _i0));
 forall _i0 in [1,1,100000),(<= (select a (- _i0 1)) (select a _i0));
 
--------[B16] in ::--------

----------[B16]-> [B15] out -------:
(= swapped 1);
 
--------[B17] in ::--------

----------[B17]-> [B16] out -------:

