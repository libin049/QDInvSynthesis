*******************process function::  main***************
--------[B0] in ::--------
(>= i (div 100000 2));
 (>= x (div 100000 2));
 (= _ret 0);
 exist _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,i),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(- x 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 
--------[B1] in ::--------
(>= i (div 100000 2));
 (>= x (div 100000 2));
 exist _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,i),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(- x 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 
----------[B1]-> [B0] out -------:
(>= i (div 100000 2));
 (>= x (div 100000 2));
 (= _ret 0);
 exist _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,i),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(- x 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 
--------[B2] in ::--------
(>= i (div 100000 2));
 (< x i);
 (< x (div 100000 2));
 exist _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,i),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 {forall _i0 in [0,1,(- x 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)))} || {(= x 0)};
 forall _i0 in [0,1,x],(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 
----------[B2]-> [B3] out -------:
(>= i (div 100000 2));
 exist _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,i),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(- x 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 
--------[B3] in ::--------
(>= i (div 100000 2));
 exist _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,i),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 {forall _i0 in [0,1,(- x 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)))} || {(= x 0)};
 
----------[B3]-> [B2] out -------:
(>= i (div 100000 2));
 (< x i);
 (< x (div 100000 2));
 exist _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,i),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 {forall _i0 in [0,1,(- x 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)))} || {(= x 0)};
 forall _i0 in [0,1,x],(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 
----------[B3]-> [B1] out -------:
(>= i (div 100000 2));
 (>= x (div 100000 2));
 exist _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,i),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(- x 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 
--------[B4] in ::--------
(>= i (div 100000 2));
 exist _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,i),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 
----------[B4]-> [B3] out -------:
(>= i (div 100000 2));
 (= x 0);
 exist _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,i),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 
--------[B5] in ::--------
(< i (div 100000 2));
 (= (select A i) (select A (- (- 100000 i) 1)));
 exist _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,i),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)))} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 
----------[B5]-> [B7] out -------:
exist _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,i),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 
--------[B6] in ::--------
(< i (div 100000 2));
 forall _i0 in [0,1,i),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 {exist _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)))} || {(= i 0)};
 
----------[B6]-> [B5] out -------:
(< i (div 100000 2));
 (= (select A i) (select A (- (- 100000 i) 1)));
 exist _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,i),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)))} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 
--------[B7] in ::--------
forall _i0 in [0,1,i),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 {exist _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)))} || {(= i 0)};
 
----------[B7]-> [B6] out -------:
(< i (div 100000 2));
 forall _i0 in [0,1,i),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 {exist _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)))} || {(= i 0)};
 
----------[B7]-> [B4] out -------:
(>= i (div 100000 2));
 exist _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,i),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 forall _i0 in [0,1,(div 100000 2)),(= (select A _i0) (select A (- (- 100000 _i0) 1)));
 
--------[B8] in ::--------

----------[B8]-> [B7] out -------:
(= i 0);
 
--------[B9] in ::--------

----------[B9]-> [B8] out -------:

