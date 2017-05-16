*******************process function::  main***************
--------[B0] in ::--------
(>= i 100000);
 (>= x 100000);
 (= _ret 0);
 exist _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 exist _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 exist _i0 in [0,1,100000),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,i),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,i),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(- x 1)),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- x 1)),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(- x 1)),(= (select a1 _i0) (select a2 _i0));
 
--------[B1] in ::--------
(>= i 100000);
 (>= x 100000);
 exist _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 exist _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 exist _i0 in [0,1,100000),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,i),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,i),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(- x 1)),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- x 1)),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(- x 1)),(= (select a1 _i0) (select a2 _i0));
 
----------[B1]-> [B0] out -------:
(>= i 100000);
 (>= x 100000);
 (= _ret 0);
 exist _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 exist _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 exist _i0 in [0,1,100000),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,i),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,i),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(- x 1)),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- x 1)),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(- x 1)),(= (select a1 _i0) (select a2 _i0));
 
--------[B2] in ::--------
(>= i 100000);
 (< x i);
 (< x 100000);
 exist _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 exist _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 exist _i0 in [0,1,100000),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,i),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,i),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 {forall _i0 in [0,1,(- x 1)),(= (select a3 _i0) (select a1 _i0))} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(= (select a2 _i0) (select a3 _i0))} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(= (select a1 _i0) (select a2 _i0))} || {(= x 0)};
 forall _i0 in [0,1,x],(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,x],(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,x],(= (select a1 _i0) (select a2 _i0));
 
----------[B2]-> [B3] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 exist _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 exist _i0 in [0,1,100000),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,i),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,i),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(- x 1)),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- x 1)),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(- x 1)),(= (select a1 _i0) (select a2 _i0));
 
--------[B3] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 exist _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 exist _i0 in [0,1,100000),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,i),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,i),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 {forall _i0 in [0,1,(- x 1)),(= (select a3 _i0) (select a1 _i0))} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(= (select a2 _i0) (select a3 _i0))} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(= (select a1 _i0) (select a2 _i0))} || {(= x 0)};
 
----------[B3]-> [B2] out -------:
(>= i 100000);
 (< x i);
 (< x 100000);
 exist _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 exist _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 exist _i0 in [0,1,100000),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,i),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,i),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 {forall _i0 in [0,1,(- x 1)),(= (select a3 _i0) (select a1 _i0))} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(= (select a2 _i0) (select a3 _i0))} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(= (select a1 _i0) (select a2 _i0))} || {(= x 0)};
 forall _i0 in [0,1,x],(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,x],(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,x],(= (select a1 _i0) (select a2 _i0));
 
----------[B3]-> [B1] out -------:
(>= i 100000);
 (>= x 100000);
 exist _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 exist _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 exist _i0 in [0,1,100000),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,i),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,i),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(- x 1)),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- x 1)),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(- x 1)),(= (select a1 _i0) (select a2 _i0));
 
--------[B4] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 exist _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 exist _i0 in [0,1,100000),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,i),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,i),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 
----------[B4]-> [B3] out -------:
(>= i 100000);
 (= x 0);
 exist _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 exist _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 exist _i0 in [0,1,100000),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,i),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,i),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 
--------[B5] in ::--------
(= (select a3 i) (select a1 i));
 (= (select a2 i) (select a3 i));
 (= (select a1 i) (select a2 i));
 (< i 100000);
 exist _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 exist _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 exist _i0 in [0,1,100000),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,i),(= (select a1 _i0) (select a2 _i0));
 {forall _i0 in [0,1,(- i 1)),(= (select a3 _i0) (select a1 _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a3 _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a1 _i0) (select a2 _i0))} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,(+ i 1)),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(+ i 1)),(= (select a1 _i0) (select a2 _i0));
 
----------[B5]-> [B7] out -------:
exist _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 exist _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 exist _i0 in [0,1,100000),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,i),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,i),(= (select a1 _i0) (select a2 _i0));
 
--------[B6] in ::--------
(< i 100000);
 exist _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,i),(= (select a1 _i0) (select a2 _i0));
 {exist _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0))} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0))} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a1 _i0) (select a2 _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a3 _i0) (select a1 _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a3 _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a1 _i0) (select a2 _i0))} || {(= i 0)};
 
----------[B6]-> [B5] out -------:
(= (select a3 i) (select a1 i));
 (= (select a2 i) (select a3 i));
 (= (select a1 i) (select a2 i));
 (< i 100000);
 exist _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 exist _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 exist _i0 in [0,1,100000),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,i),(= (select a1 _i0) (select a2 _i0));
 {forall _i0 in [0,1,(- i 1)),(= (select a3 _i0) (select a1 _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a3 _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a1 _i0) (select a2 _i0))} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,(+ i 1)),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(+ i 1)),(= (select a1 _i0) (select a2 _i0));
 
--------[B7] in ::--------
exist _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,i),(= (select a1 _i0) (select a2 _i0));
 {exist _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0))} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0))} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a1 _i0) (select a2 _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a3 _i0) (select a1 _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a3 _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a1 _i0) (select a2 _i0))} || {(= i 0)};
 
----------[B7]-> [B6] out -------:
(< i 100000);
 exist _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,i),(= (select a1 _i0) (select a2 _i0));
 {exist _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0))} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0))} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a1 _i0) (select a2 _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a3 _i0) (select a1 _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a3 _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a1 _i0) (select a2 _i0))} || {(= i 0)};
 
----------[B7]-> [B4] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 exist _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 exist _i0 in [0,1,100000),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,i),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a3 _i0));
 forall _i0 in [0,1,i),(= (select a1 _i0) (select a2 _i0));
 forall _i0 in [0,1,100000),(= (select a3 _i0) (select a1 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a3 _i0));
 
--------[B8] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 
----------[B8]-> [B7] out -------:
(= i 0);
 exist _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 
--------[B9] in ::--------
(< i 100000);
 (= (select a2 i) (select a1 i));
 exist _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a1 _i0));
 {forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a1 _i0))} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),(= (select a2 _i0) (select a1 _i0));
 
----------[B9]-> [B11] out -------:
exist _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a1 _i0));
 
--------[B10] in ::--------
(< i 100000);
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a1 _i0));
 {exist _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a1 _i0))} || {(= i 0)};
 
----------[B10]-> [B9] out -------:
(< i 100000);
 (= (select a2 i) (select a1 i));
 exist _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a1 _i0));
 {forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a1 _i0))} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),(= (select a2 _i0) (select a1 _i0));
 
--------[B11] in ::--------
forall _i0 in [0,1,i),(= (select a2 _i0) (select a1 _i0));
 {exist _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a1 _i0))} || {(= i 0)};
 
----------[B11]-> [B10] out -------:
(< i 100000);
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a1 _i0));
 {exist _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a1 _i0))} || {(= i 0)};
 
----------[B11]-> [B8] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,i),(= (select a2 _i0) (select a1 _i0));
 forall _i0 in [0,1,100000),(= (select a2 _i0) (select a1 _i0));
 
--------[B12] in ::--------

----------[B12]-> [B11] out -------:
(= i 0);
 
--------[B13] in ::--------

----------[B13]-> [B12] out -------:

