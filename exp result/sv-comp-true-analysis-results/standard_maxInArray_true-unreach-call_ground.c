*******************process function::  main***************
--------[B0] in ::--------
(>= i 100000);
 (>= x 100000);
 (= _ret 0);
 exist _i0 in [0,1,100000),(<= (select a _i0) max);
 forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max);
 forall _i0 in [0,1,i),(<= (select a _i0) max);
 forall _i0 in [0,1,100000),(<= (select a _i0) max);
 {exist _i0 in [0,1,100000),(= max (select a _i0))} || {(= max 0)};
 forall _i0 in [0,1,(- x 1)),(<= (select a _i0) max);
 
--------[B1] in ::--------
(>= i 100000);
 (>= x 100000);
 exist _i0 in [0,1,100000),(<= (select a _i0) max);
 forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max);
 forall _i0 in [0,1,i),(<= (select a _i0) max);
 forall _i0 in [0,1,100000),(<= (select a _i0) max);
 {exist _i0 in [0,1,100000),(= max (select a _i0))} || {(= max 0)};
 forall _i0 in [0,1,(- x 1)),(<= (select a _i0) max);
 
----------[B1]-> [B0] out -------:
(>= i 100000);
 (>= x 100000);
 (= _ret 0);
 exist _i0 in [0,1,100000),(<= (select a _i0) max);
 forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max);
 forall _i0 in [0,1,i),(<= (select a _i0) max);
 forall _i0 in [0,1,100000),(<= (select a _i0) max);
 {exist _i0 in [0,1,100000),(= max (select a _i0))} || {(= max 0)};
 forall _i0 in [0,1,(- x 1)),(<= (select a _i0) max);
 
--------[B2] in ::--------
(>= i 100000);
 (< x i);
 (< x 100000);
 exist _i0 in [0,1,100000),(<= (select a _i0) max);
 forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max);
 forall _i0 in [0,1,i),(<= (select a _i0) max);
 forall _i0 in [0,1,100000),(<= (select a _i0) max);
 {exist _i0 in [0,1,100000),(= max (select a _i0))} || {(= max 0)};
 {forall _i0 in [0,1,(- x 1)),(<= (select a _i0) max)} || {(= x 0)};
 forall _i0 in [0,1,x],(<= (select a _i0) max);
 
----------[B2]-> [B3] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(<= (select a _i0) max);
 forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max);
 forall _i0 in [0,1,i),(<= (select a _i0) max);
 forall _i0 in [0,1,100000),(<= (select a _i0) max);
 {exist _i0 in [0,1,100000),(= max (select a _i0))} || {(= max 0)};
 forall _i0 in [0,1,(- x 1)),(<= (select a _i0) max);
 
--------[B3] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(<= (select a _i0) max);
 forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max);
 forall _i0 in [0,1,i),(<= (select a _i0) max);
 forall _i0 in [0,1,100000),(<= (select a _i0) max);
 {exist _i0 in [0,1,100000),(= max (select a _i0))} || {(= max 0)};
 {forall _i0 in [0,1,(- x 1)),(<= (select a _i0) max)} || {(= x 0)};
 
----------[B3]-> [B2] out -------:
(>= i 100000);
 (< x i);
 (< x 100000);
 exist _i0 in [0,1,100000),(<= (select a _i0) max);
 forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max);
 forall _i0 in [0,1,i),(<= (select a _i0) max);
 forall _i0 in [0,1,100000),(<= (select a _i0) max);
 {exist _i0 in [0,1,100000),(= max (select a _i0))} || {(= max 0)};
 {forall _i0 in [0,1,(- x 1)),(<= (select a _i0) max)} || {(= x 0)};
 forall _i0 in [0,1,x],(<= (select a _i0) max);
 
----------[B3]-> [B1] out -------:
(>= i 100000);
 (>= x 100000);
 exist _i0 in [0,1,100000),(<= (select a _i0) max);
 forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max);
 forall _i0 in [0,1,i),(<= (select a _i0) max);
 forall _i0 in [0,1,100000),(<= (select a _i0) max);
 {exist _i0 in [0,1,100000),(= max (select a _i0))} || {(= max 0)};
 forall _i0 in [0,1,(- x 1)),(<= (select a _i0) max);
 
--------[B4] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(<= (select a _i0) max);
 {exist _i0 in [0,1,100000),(= max (select a _i0))} || {(= max 0)};
 forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max);
 forall _i0 in [0,1,i),(<= (select a _i0) max);
 forall _i0 in [0,1,100000),(<= (select a _i0) max);
 
----------[B4]-> [B3] out -------:
(>= i 100000);
 (= x 0);
 exist _i0 in [0,1,100000),(<= (select a _i0) max);
 {exist _i0 in [0,1,100000),(= max (select a _i0))} || {(= max 0)};
 forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max);
 forall _i0 in [0,1,i),(<= (select a _i0) max);
 forall _i0 in [0,1,100000),(<= (select a _i0) max);
 
--------[B5] in ::--------
exist _i0 in [0,1,100000),(<= (select a _i0) max);
 {exist _i0 in [0,1,100000),(= max (select a _i0))} || {(= max 0)};
 forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max);
 forall _i0 in [0,1,i),(<= (select a _i0) max);
 
----------[B5]-> [B9] out -------:
exist _i0 in [0,1,100000),(<= (select a _i0) max);
 {exist _i0 in [0,1,100000),(= max (select a _i0))} || {(= max 0)};
 forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max);
 forall _i0 in [0,1,i),(<= (select a _i0) max);
 
--------[B6] in ::--------
(< i 100000);
 (<= (select a i) max);
 exist _i0 in [0,1,100000),(<= (select a _i0) max);
 forall _i0 in [0,1,i),(<= (select a _i0) max);
 forall _i0 in [0,1,(+ i 1)),(<= (select a _i0) max);
 {exist _i0 in [0,1,100000),(= max (select a _i0))} || {(= max 0)};
 
----------[B6]-> [B5] out -------:
exist _i0 in [0,1,100000),(<= (select a _i0) max);
 {exist _i0 in [0,1,100000),(= max (select a _i0))} || {(= max 0)};
 forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max);
 forall _i0 in [0,1,i),(<= (select a _i0) max);
 
--------[B7] in ::--------
(< i 100000);
 (> (select a i) max);
 forall _i0 in [0,1,i),(<= (select a _i0) max);
 {exist _i0 in [0,1,100000),(= max (select a _i0))} || {(= max 0)};
 {exist _i0 in [0,1,100000),(<= (select a _i0) max)} || {(= max 0)};
 {exist _i0 in [0,1,100000),(<= (select a _i0) max)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max)} || {(= max 0)};
 {forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max)} || {(= i 0)};
 forall _i0 in [0,1,i),(< (select a _i0) (select a i));
 exist _i0 in [0,1,100000),(> (select a _i0) max);
 exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(< (select a _i0) (select a _i1));
 
----------[B7]-> [B6] out -------:
(< i 100000);
 (= max (select a i));
 exist _i0 in [0,1,100000),(= max (select a _i0));
 forall _i0 in [0,1,i),(< (select a _i0) (select a i));
 exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(< (select a _i0) (select a _i1));
 forall _i0 in [0,1,i),(< (select a _i0) max);
 forall _i0 in [0,1,(+ i 1)),(<= (select a _i0) max);
 
--------[B8] in ::--------
(< i 100000);
 forall _i0 in [0,1,i),(<= (select a _i0) max);
 {exist _i0 in [0,1,100000),(= max (select a _i0))} || {(= max 0)};
 {exist _i0 in [0,1,100000),(<= (select a _i0) max)} || {(= max 0)};
 {exist _i0 in [0,1,100000),(<= (select a _i0) max)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max)} || {(= max 0)};
 {forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max)} || {(= i 0)};
 
----------[B8]-> [B7] out -------:
(< i 100000);
 (> (select a i) max);
 forall _i0 in [0,1,i),(<= (select a _i0) max);
 {exist _i0 in [0,1,100000),(= max (select a _i0))} || {(= max 0)};
 {exist _i0 in [0,1,100000),(<= (select a _i0) max)} || {(= max 0)};
 {exist _i0 in [0,1,100000),(<= (select a _i0) max)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max)} || {(= max 0)};
 {forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max)} || {(= i 0)};
 forall _i0 in [0,1,i),(< (select a _i0) (select a i));
 exist _i0 in [0,1,100000),(> (select a _i0) max);
 exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(< (select a _i0) (select a _i1));
 
----------[B8]-> [B6] out -------:
(< i 100000);
 (<= (select a i) max);
 forall _i0 in [0,1,i),(<= (select a _i0) max);
 {exist _i0 in [0,1,100000),(= max (select a _i0))} || {(= max 0)};
 {forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max)} || {(= max 0)};
 {forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max)} || {(= i 0)};
 exist _i0 in [0,1,100000),(<= (select a _i0) max);
 forall _i0 in [0,1,(+ i 1)),(<= (select a _i0) max);
 
--------[B9] in ::--------
forall _i0 in [0,1,i),(<= (select a _i0) max);
 {exist _i0 in [0,1,100000),(= max (select a _i0))} || {(= max 0)};
 {exist _i0 in [0,1,100000),(<= (select a _i0) max)} || {(= max 0)};
 {exist _i0 in [0,1,100000),(<= (select a _i0) max)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max)} || {(= max 0)};
 {forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max)} || {(= i 0)};
 
----------[B9]-> [B8] out -------:
(< i 100000);
 forall _i0 in [0,1,i),(<= (select a _i0) max);
 {exist _i0 in [0,1,100000),(= max (select a _i0))} || {(= max 0)};
 {exist _i0 in [0,1,100000),(<= (select a _i0) max)} || {(= max 0)};
 {exist _i0 in [0,1,100000),(<= (select a _i0) max)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max)} || {(= max 0)};
 {forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max)} || {(= i 0)};
 
----------[B9]-> [B4] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(<= (select a _i0) max);
 {exist _i0 in [0,1,100000),(= max (select a _i0))} || {(= max 0)};
 forall _i0 in [0,1,(- i 1)),(<= (select a _i0) max);
 forall _i0 in [0,1,i),(<= (select a _i0) max);
 forall _i0 in [0,1,100000),(<= (select a _i0) max);
 
--------[B10] in ::--------

----------[B10]-> [B9] out -------:
(= max 0);
 (= i 0);
 
--------[B11] in ::--------

----------[B11]-> [B10] out -------:

