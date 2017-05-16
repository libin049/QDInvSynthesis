*******************process function::  main***************
--------[B0] in ::--------
(>= i 100000);
 (>= x 100000);
 (= _ret 0);
 exist _i0 in [1,1,100000),(>= largest (select array _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest);
 forall _i0 in [1,1,i),(<= (select array _i0) largest);
 forall _i0 in [1,1,100000),(<= (select array _i0) largest);
 {exist _i0 in [1,1,100000),(= largest (select array _i0))} || {(= largest (select array 0))};
 forall _i0 in [1,1,0],(<= (select array _i0) largest);
 forall _i0 in [1,1,(- x 1)),(<= (select array _i0) largest);
 
--------[B1] in ::--------
(>= i 100000);
 (>= x 100000);
 exist _i0 in [1,1,100000),(>= largest (select array _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest);
 forall _i0 in [1,1,i),(<= (select array _i0) largest);
 forall _i0 in [1,1,100000),(<= (select array _i0) largest);
 {exist _i0 in [1,1,100000),(= largest (select array _i0))} || {(= largest (select array 0))};
 forall _i0 in [1,1,0],(<= (select array _i0) largest);
 forall _i0 in [1,1,(- x 1)),(<= (select array _i0) largest);
 
----------[B1]-> [B0] out -------:
(>= i 100000);
 (>= x 100000);
 (= _ret 0);
 exist _i0 in [1,1,100000),(>= largest (select array _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest);
 forall _i0 in [1,1,i),(<= (select array _i0) largest);
 forall _i0 in [1,1,100000),(<= (select array _i0) largest);
 {exist _i0 in [1,1,100000),(= largest (select array _i0))} || {(= largest (select array 0))};
 forall _i0 in [1,1,0],(<= (select array _i0) largest);
 forall _i0 in [1,1,(- x 1)),(<= (select array _i0) largest);
 
--------[B2] in ::--------
(>= i 100000);
 (< x i);
 (< x 100000);
 exist _i0 in [1,1,100000),(>= largest (select array _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest);
 forall _i0 in [1,1,i),(<= (select array _i0) largest);
 forall _i0 in [1,1,100000),(<= (select array _i0) largest);
 {exist _i0 in [1,1,100000),(= largest (select array _i0))} || {(= largest (select array 0))};
 {forall _i0 in [1,1,(- x 1)),(<= (select array _i0) largest)} || {(= x 0)};
 forall _i0 in [1,1,x],(<= (select array _i0) largest);
 forall _i0 in [1,1,0],(<= (select array _i0) largest);
 
----------[B2]-> [B3] out -------:
(>= i 100000);
 exist _i0 in [1,1,100000),(>= largest (select array _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest);
 forall _i0 in [1,1,i),(<= (select array _i0) largest);
 forall _i0 in [1,1,100000),(<= (select array _i0) largest);
 {exist _i0 in [1,1,100000),(= largest (select array _i0))} || {(= largest (select array 0))};
 forall _i0 in [1,1,0],(<= (select array _i0) largest);
 forall _i0 in [1,1,(- x 1)),(<= (select array _i0) largest);
 
--------[B3] in ::--------
(>= i 100000);
 exist _i0 in [1,1,100000),(>= largest (select array _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest);
 forall _i0 in [1,1,i),(<= (select array _i0) largest);
 forall _i0 in [1,1,100000),(<= (select array _i0) largest);
 {exist _i0 in [1,1,100000),(= largest (select array _i0))} || {(= largest (select array 0))};
 {forall _i0 in [1,1,0],(<= (select array _i0) largest)} || {(= x 0)};
 {forall _i0 in [1,1,(- x 1)),(<= (select array _i0) largest)} || {(= x 0)};
 
----------[B3]-> [B2] out -------:
(>= i 100000);
 (< x i);
 (< x 100000);
 exist _i0 in [1,1,100000),(>= largest (select array _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest);
 forall _i0 in [1,1,i),(<= (select array _i0) largest);
 forall _i0 in [1,1,100000),(<= (select array _i0) largest);
 {exist _i0 in [1,1,100000),(= largest (select array _i0))} || {(= largest (select array 0))};
 {forall _i0 in [1,1,0],(<= (select array _i0) largest)} || {(= x 0)};
 {forall _i0 in [1,1,(- x 1)),(<= (select array _i0) largest)} || {(= x 0)};
 forall _i0 in [1,1,x],(<= (select array _i0) largest);
 
----------[B3]-> [B1] out -------:
(>= i 100000);
 (>= x 100000);
 exist _i0 in [1,1,100000),(>= largest (select array _i0));
 forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest);
 forall _i0 in [1,1,i),(<= (select array _i0) largest);
 forall _i0 in [1,1,100000),(<= (select array _i0) largest);
 {exist _i0 in [1,1,100000),(= largest (select array _i0))} || {(= largest (select array 0))};
 forall _i0 in [1,1,0],(<= (select array _i0) largest);
 forall _i0 in [1,1,(- x 1)),(<= (select array _i0) largest);
 
--------[B4] in ::--------
(>= i 100000);
 exist _i0 in [1,1,100000),(>= largest (select array _i0));
 {exist _i0 in [1,1,100000),(= largest (select array _i0))} || {(= largest (select array 0))};
 forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest);
 forall _i0 in [1,1,i),(<= (select array _i0) largest);
 forall _i0 in [1,1,100000),(<= (select array _i0) largest);
 
----------[B4]-> [B3] out -------:
(>= i 100000);
 (= x 0);
 exist _i0 in [1,1,100000),(>= largest (select array _i0));
 {exist _i0 in [1,1,100000),(= largest (select array _i0))} || {(= largest (select array 0))};
 forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest);
 forall _i0 in [1,1,i),(<= (select array _i0) largest);
 forall _i0 in [1,1,100000),(<= (select array _i0) largest);
 
--------[B5] in ::--------
(< i 100000);
 (>= largest (select array i));
 exist _i0 in [1,1,100000),(>= largest (select array _i0));
 forall _i0 in [1,1,i),(<= (select array _i0) largest);
 forall _i0 in [1,1,(+ i 1)),(<= (select array _i0) largest);
 {exist _i0 in [1,1,100000),(= largest (select array _i0))} || {(= largest (select array 0))};
 
----------[B5]-> [B8] out -------:
exist _i0 in [1,1,100000),(>= largest (select array _i0));
 {exist _i0 in [1,1,100000),(= largest (select array _i0))} || {(= largest (select array 0))};
 forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest);
 forall _i0 in [1,1,i),(<= (select array _i0) largest);
 
--------[B6] in ::--------
(< i 100000);
 (< largest (select array i));
 forall _i0 in [1,1,i),(<= (select array _i0) largest);
 {exist _i0 in [1,1,100000),(= largest (select array _i0))} || {(= largest (select array 0))};
 {exist _i0 in [1,1,100000),(>= largest (select array _i0))} || {(= largest (select array 0))};
 {exist _i0 in [1,1,100000),(>= largest (select array _i0))} || {(= i 1)};
 {forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest)} || {(= largest (select array 0))};
 {forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest)} || {(= i 1)};
 forall _i0 in [1,1,i),(< (select array _i0) (select array i));
 exist _i0 in [1,1,100000),(< largest (select array _i0));
 exist _i1 in [1,1,100000),forall _i0 in [1,1,_i1),(< (select array _i0) (select array _i1));
 
----------[B6]-> [B5] out -------:
(< i 100000);
 (= largest (select array i));
 exist _i0 in [1,1,100000),(= largest (select array _i0));
 forall _i0 in [1,1,i),(< (select array _i0) (select array i));
 exist _i1 in [1,1,100000),forall _i0 in [1,1,_i1),(< (select array _i0) (select array _i1));
 forall _i0 in [1,1,i),(< (select array _i0) largest);
 forall _i0 in [1,1,(+ i 1)),(<= (select array _i0) largest);
 
--------[B7] in ::--------
(< i 100000);
 forall _i0 in [1,1,i),(<= (select array _i0) largest);
 {exist _i0 in [1,1,100000),(= largest (select array _i0))} || {(= largest (select array 0))};
 {exist _i0 in [1,1,100000),(>= largest (select array _i0))} || {(= largest (select array 0))};
 {exist _i0 in [1,1,100000),(>= largest (select array _i0))} || {(= i 1)};
 {forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest)} || {(= largest (select array 0))};
 {forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest)} || {(= i 1)};
 
----------[B7]-> [B6] out -------:
(< i 100000);
 (< largest (select array i));
 forall _i0 in [1,1,i),(<= (select array _i0) largest);
 {exist _i0 in [1,1,100000),(= largest (select array _i0))} || {(= largest (select array 0))};
 {exist _i0 in [1,1,100000),(>= largest (select array _i0))} || {(= largest (select array 0))};
 {exist _i0 in [1,1,100000),(>= largest (select array _i0))} || {(= i 1)};
 {forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest)} || {(= largest (select array 0))};
 {forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest)} || {(= i 1)};
 forall _i0 in [1,1,i),(< (select array _i0) (select array i));
 exist _i0 in [1,1,100000),(< largest (select array _i0));
 exist _i1 in [1,1,100000),forall _i0 in [1,1,_i1),(< (select array _i0) (select array _i1));
 
----------[B7]-> [B5] out -------:
(< i 100000);
 (>= largest (select array i));
 forall _i0 in [1,1,i),(<= (select array _i0) largest);
 {exist _i0 in [1,1,100000),(= largest (select array _i0))} || {(= largest (select array 0))};
 {forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest)} || {(= largest (select array 0))};
 {forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest)} || {(= i 1)};
 exist _i0 in [1,1,100000),(>= largest (select array _i0));
 forall _i0 in [1,1,(+ i 1)),(<= (select array _i0) largest);
 
--------[B8] in ::--------
forall _i0 in [1,1,i),(<= (select array _i0) largest);
 {exist _i0 in [1,1,100000),(= largest (select array _i0))} || {(= largest (select array 0))};
 {exist _i0 in [1,1,100000),(>= largest (select array _i0))} || {(= largest (select array 0))};
 {exist _i0 in [1,1,100000),(>= largest (select array _i0))} || {(= i 1)};
 {forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest)} || {(= largest (select array 0))};
 {forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest)} || {(= i 1)};
 
----------[B8]-> [B7] out -------:
(< i 100000);
 forall _i0 in [1,1,i),(<= (select array _i0) largest);
 {exist _i0 in [1,1,100000),(= largest (select array _i0))} || {(= largest (select array 0))};
 {exist _i0 in [1,1,100000),(>= largest (select array _i0))} || {(= largest (select array 0))};
 {exist _i0 in [1,1,100000),(>= largest (select array _i0))} || {(= i 1)};
 {forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest)} || {(= largest (select array 0))};
 {forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest)} || {(= i 1)};
 
----------[B8]-> [B4] out -------:
(>= i 100000);
 exist _i0 in [1,1,100000),(>= largest (select array _i0));
 {exist _i0 in [1,1,100000),(= largest (select array _i0))} || {(= largest (select array 0))};
 forall _i0 in [1,1,(- i 1)),(<= (select array _i0) largest);
 forall _i0 in [1,1,i),(<= (select array _i0) largest);
 forall _i0 in [1,1,100000),(<= (select array _i0) largest);
 
--------[B9] in ::--------

----------[B9]-> [B8] out -------:
(= largest (select array 0));
 (= i 1);
 
--------[B10] in ::--------

----------[B10]-> [B9] out -------:

