*******************process function::  main***************
--------[B0] in ::--------
(>= i 100000);
 (>= x 100000);
 (= _ret 0);
 exist _i0 in [0,1,100000),(>= (select a _i0) min);
 forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min);
 forall _i0 in [0,1,i),(>= (select a _i0) min);
 forall _i0 in [0,1,100000),(>= (select a _i0) min);
 {exist _i0 in [0,1,100000),(= min (select a _i0))} || {(= min 0)};
 {(= min 0)} || {forall _i0 in [0,1,i),(<= min (select a _i0))};
 {(= min 0)} || {forall _i0 in [0,1,100000),(<= min (select a _i0))};
 forall _i0 in [0,1,(- x 1)),(>= (select a _i0) min);
 {(= min 0)} || {forall _i0 in [0,1,(- x 1)),(<= min (select a _i0))};
 
--------[B1] in ::--------
(>= i 100000);
 (>= x 100000);
 exist _i0 in [0,1,100000),(>= (select a _i0) min);
 forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min);
 forall _i0 in [0,1,i),(>= (select a _i0) min);
 forall _i0 in [0,1,100000),(>= (select a _i0) min);
 {exist _i0 in [0,1,100000),(= min (select a _i0))} || {(= min 0)};
 {(= min 0)} || {forall _i0 in [0,1,i),(<= min (select a _i0))};
 {(= min 0)} || {forall _i0 in [0,1,100000),(<= min (select a _i0))};
 forall _i0 in [0,1,(- x 1)),(>= (select a _i0) min);
 {(= min 0)} || {forall _i0 in [0,1,(- x 1)),(<= min (select a _i0))};
 
----------[B1]-> [B0] out -------:
(>= i 100000);
 (>= x 100000);
 (= _ret 0);
 exist _i0 in [0,1,100000),(>= (select a _i0) min);
 forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min);
 forall _i0 in [0,1,i),(>= (select a _i0) min);
 forall _i0 in [0,1,100000),(>= (select a _i0) min);
 {exist _i0 in [0,1,100000),(= min (select a _i0))} || {(= min 0)};
 {(= min 0)} || {forall _i0 in [0,1,i),(<= min (select a _i0))};
 {(= min 0)} || {forall _i0 in [0,1,100000),(<= min (select a _i0))};
 forall _i0 in [0,1,(- x 1)),(>= (select a _i0) min);
 {(= min 0)} || {forall _i0 in [0,1,(- x 1)),(<= min (select a _i0))};
 
--------[B2] in ::--------
(>= i 100000);
 (< x i);
 (< x 100000);
 exist _i0 in [0,1,100000),(>= (select a _i0) min);
 forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min);
 forall _i0 in [0,1,i),(>= (select a _i0) min);
 forall _i0 in [0,1,100000),(>= (select a _i0) min);
 {exist _i0 in [0,1,100000),(= min (select a _i0))} || {(= min 0)};
 {(= min 0)} || {forall _i0 in [0,1,i),(<= min (select a _i0))};
 {(= min 0)} || {forall _i0 in [0,1,100000),(<= min (select a _i0))};
 {forall _i0 in [0,1,(- x 1)),(>= (select a _i0) min)} || {(= x 0)};
 forall _i0 in [0,1,x],(>= (select a _i0) min);
 {(= min 0)} || {forall _i0 in [0,1,x],(<= min (select a _i0))};
 
----------[B2]-> [B3] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(>= (select a _i0) min);
 forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min);
 forall _i0 in [0,1,i),(>= (select a _i0) min);
 forall _i0 in [0,1,100000),(>= (select a _i0) min);
 {exist _i0 in [0,1,100000),(= min (select a _i0))} || {(= min 0)};
 {(= min 0)} || {forall _i0 in [0,1,i),(<= min (select a _i0))};
 {(= min 0)} || {forall _i0 in [0,1,100000),(<= min (select a _i0))};
 forall _i0 in [0,1,(- x 1)),(>= (select a _i0) min);
 {(= min 0)} || {forall _i0 in [0,1,(- x 1)),(<= min (select a _i0))};
 
--------[B3] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(>= (select a _i0) min);
 forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min);
 forall _i0 in [0,1,i),(>= (select a _i0) min);
 forall _i0 in [0,1,100000),(>= (select a _i0) min);
 {exist _i0 in [0,1,100000),(= min (select a _i0))} || {(= min 0)};
 {(= min 0)} || {forall _i0 in [0,1,i),(<= min (select a _i0))};
 {(= min 0)} || {forall _i0 in [0,1,100000),(<= min (select a _i0))};
 {forall _i0 in [0,1,(- x 1)),(>= (select a _i0) min)} || {(= x 0)};
 
----------[B3]-> [B2] out -------:
(>= i 100000);
 (< x i);
 (< x 100000);
 exist _i0 in [0,1,100000),(>= (select a _i0) min);
 forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min);
 forall _i0 in [0,1,i),(>= (select a _i0) min);
 forall _i0 in [0,1,100000),(>= (select a _i0) min);
 {exist _i0 in [0,1,100000),(= min (select a _i0))} || {(= min 0)};
 {(= min 0)} || {forall _i0 in [0,1,i),(<= min (select a _i0))};
 {(= min 0)} || {forall _i0 in [0,1,100000),(<= min (select a _i0))};
 {forall _i0 in [0,1,(- x 1)),(>= (select a _i0) min)} || {(= x 0)};
 forall _i0 in [0,1,x],(>= (select a _i0) min);
 {(= min 0)} || {forall _i0 in [0,1,x],(<= min (select a _i0))};
 
----------[B3]-> [B1] out -------:
(>= i 100000);
 (>= x 100000);
 exist _i0 in [0,1,100000),(>= (select a _i0) min);
 forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min);
 forall _i0 in [0,1,i),(>= (select a _i0) min);
 forall _i0 in [0,1,100000),(>= (select a _i0) min);
 {exist _i0 in [0,1,100000),(= min (select a _i0))} || {(= min 0)};
 {(= min 0)} || {forall _i0 in [0,1,i),(<= min (select a _i0))};
 {(= min 0)} || {forall _i0 in [0,1,100000),(<= min (select a _i0))};
 forall _i0 in [0,1,(- x 1)),(>= (select a _i0) min);
 {(= min 0)} || {forall _i0 in [0,1,(- x 1)),(<= min (select a _i0))};
 
--------[B4] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(>= (select a _i0) min);
 {exist _i0 in [0,1,100000),(= min (select a _i0))} || {(= min 0)};
 forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min);
 forall _i0 in [0,1,i),(>= (select a _i0) min);
 {(= min 0)} || {forall _i0 in [0,1,i),(<= min (select a _i0))};
 forall _i0 in [0,1,100000),(>= (select a _i0) min);
 {(= min 0)} || {forall _i0 in [0,1,100000),(<= min (select a _i0))};
 
----------[B4]-> [B3] out -------:
(>= i 100000);
 (= x 0);
 exist _i0 in [0,1,100000),(>= (select a _i0) min);
 {exist _i0 in [0,1,100000),(= min (select a _i0))} || {(= min 0)};
 forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min);
 forall _i0 in [0,1,i),(>= (select a _i0) min);
 {(= min 0)} || {forall _i0 in [0,1,i),(<= min (select a _i0))};
 forall _i0 in [0,1,100000),(>= (select a _i0) min);
 {(= min 0)} || {forall _i0 in [0,1,100000),(<= min (select a _i0))};
 
--------[B5] in ::--------
exist _i0 in [0,1,100000),(>= (select a _i0) min);
 {exist _i0 in [0,1,100000),(= min (select a _i0))} || {(= min 0)};
 forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min);
 forall _i0 in [0,1,i),(>= (select a _i0) min);
 {(= min 0)} || {forall _i0 in [0,1,i),(<= min (select a _i0))};
 
----------[B5]-> [B9] out -------:
exist _i0 in [0,1,100000),(>= (select a _i0) min);
 {exist _i0 in [0,1,100000),(= min (select a _i0))} || {(= min 0)};
 forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min);
 forall _i0 in [0,1,i),(>= (select a _i0) min);
 {(= min 0)} || {forall _i0 in [0,1,i),(<= min (select a _i0))};
 
--------[B6] in ::--------
(< i 100000);
 (>= (select a i) min);
 exist _i0 in [0,1,100000),(>= (select a _i0) min);
 forall _i0 in [0,1,i),(>= (select a _i0) min);
 forall _i0 in [0,1,(+ i 1)),(>= (select a _i0) min);
 {exist _i0 in [0,1,100000),(= min (select a _i0))} || {(= min 0)};
 {forall _i0 in [0,1,(+ i 1)),(<= min (select a _i0))} || {(= min 0)};
 
----------[B6]-> [B5] out -------:
exist _i0 in [0,1,100000),(>= (select a _i0) min);
 {exist _i0 in [0,1,100000),(= min (select a _i0))} || {(= min 0)};
 forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min);
 forall _i0 in [0,1,i),(>= (select a _i0) min);
 {(= min 0)} || {forall _i0 in [0,1,i),(<= min (select a _i0))};
 
--------[B7] in ::--------
(< i 100000);
 (< (select a i) min);
 forall _i0 in [0,1,i),(>= (select a _i0) min);
 {exist _i0 in [0,1,100000),(= min (select a _i0))} || {(= min 0)};
 {(= min 0)} || {forall _i0 in [0,1,i),(<= min (select a _i0))};
 {exist _i0 in [0,1,100000),(>= (select a _i0) min)} || {(= min 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) min)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min)} || {(= min 0)};
 {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min)} || {(= i 0)};
 forall _i0 in [0,1,i),(< (select a i) (select a _i0));
 exist _i0 in [0,1,100000),(< (select a _i0) min);
 exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(< (select a _i1) (select a _i0));
 
----------[B7]-> [B6] out -------:
(< i 100000);
 (= min (select a i));
 exist _i0 in [0,1,100000),(= min (select a _i0));
 forall _i0 in [0,1,i),(< (select a i) (select a _i0));
 exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(< (select a _i1) (select a _i0));
 forall _i0 in [0,1,i),(< min (select a _i0));
 forall _i0 in [0,1,(+ i 1)),(<= min (select a _i0));
 
--------[B8] in ::--------
(< i 100000);
 forall _i0 in [0,1,i),(>= (select a _i0) min);
 {exist _i0 in [0,1,100000),(= min (select a _i0))} || {(= min 0)};
 {(= min 0)} || {forall _i0 in [0,1,i),(<= min (select a _i0))};
 {exist _i0 in [0,1,100000),(>= (select a _i0) min)} || {(= min 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) min)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min)} || {(= min 0)};
 {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min)} || {(= i 0)};
 
----------[B8]-> [B7] out -------:
(< i 100000);
 (< (select a i) min);
 forall _i0 in [0,1,i),(>= (select a _i0) min);
 {exist _i0 in [0,1,100000),(= min (select a _i0))} || {(= min 0)};
 {(= min 0)} || {forall _i0 in [0,1,i),(<= min (select a _i0))};
 {exist _i0 in [0,1,100000),(>= (select a _i0) min)} || {(= min 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) min)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min)} || {(= min 0)};
 {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min)} || {(= i 0)};
 forall _i0 in [0,1,i),(< (select a i) (select a _i0));
 exist _i0 in [0,1,100000),(< (select a _i0) min);
 exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(< (select a _i1) (select a _i0));
 
----------[B8]-> [B6] out -------:
(< i 100000);
 (>= (select a i) min);
 forall _i0 in [0,1,i),(>= (select a _i0) min);
 {exist _i0 in [0,1,100000),(= min (select a _i0))} || {(= min 0)};
 {(= min 0)} || {forall _i0 in [0,1,i),(<= min (select a _i0))};
 {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min)} || {(= min 0)};
 {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min)} || {(= i 0)};
 exist _i0 in [0,1,100000),(>= (select a _i0) min);
 forall _i0 in [0,1,(+ i 1)),(>= (select a _i0) min);
 {(= min 0)} || {forall _i0 in [0,1,(+ i 1)),(<= min (select a _i0))};
 
--------[B9] in ::--------
forall _i0 in [0,1,i),(>= (select a _i0) min);
 {exist _i0 in [0,1,100000),(= min (select a _i0))} || {(= min 0)};
 {(= min 0)} || {forall _i0 in [0,1,i),(<= min (select a _i0))};
 {exist _i0 in [0,1,100000),(>= (select a _i0) min)} || {(= min 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) min)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min)} || {(= min 0)};
 {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min)} || {(= i 0)};
 
----------[B9]-> [B8] out -------:
(< i 100000);
 forall _i0 in [0,1,i),(>= (select a _i0) min);
 {exist _i0 in [0,1,100000),(= min (select a _i0))} || {(= min 0)};
 {(= min 0)} || {forall _i0 in [0,1,i),(<= min (select a _i0))};
 {exist _i0 in [0,1,100000),(>= (select a _i0) min)} || {(= min 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) min)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min)} || {(= min 0)};
 {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min)} || {(= i 0)};
 
----------[B9]-> [B4] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(>= (select a _i0) min);
 {exist _i0 in [0,1,100000),(= min (select a _i0))} || {(= min 0)};
 forall _i0 in [0,1,(- i 1)),(>= (select a _i0) min);
 forall _i0 in [0,1,i),(>= (select a _i0) min);
 {(= min 0)} || {forall _i0 in [0,1,i),(<= min (select a _i0))};
 forall _i0 in [0,1,100000),(>= (select a _i0) min);
 {(= min 0)} || {forall _i0 in [0,1,100000),(<= min (select a _i0))};
 
--------[B10] in ::--------

----------[B10]-> [B9] out -------:
(= min 0);
 (= i 0);
 
--------[B11] in ::--------

----------[B11]-> [B10] out -------:

