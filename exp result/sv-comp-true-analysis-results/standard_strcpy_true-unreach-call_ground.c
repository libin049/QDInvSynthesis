*******************process function::  main***************
--------[B0] in ::--------
(= (select src i) 0);
 (>= x i);
 (= _ret 0);
 exist _i0 in [0,1,x],(= (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- x 1)),(distinct (select src _i0) 0)} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(distinct (select dst _i0) 0)} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(= (select dst _i0) (select src _i0))} || {(= x 0)};
 
--------[B1] in ::--------
(= (select src i) 0);
 (>= x i);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- x 1)),(distinct (select src _i0) 0)} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(distinct (select dst _i0) 0)} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(= (select dst _i0) (select src _i0))} || {(= x 0)};
 exist _i0 in [0,1,x],(= (select src _i0) 0);
 
----------[B1]-> [B0] out -------:
(= (select src i) 0);
 (>= x i);
 (= _ret 0);
 exist _i0 in [0,1,x],(= (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- x 1)),(distinct (select src _i0) 0)} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(distinct (select dst _i0) 0)} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(= (select dst _i0) (select src _i0))} || {(= x 0)};
 
--------[B2] in ::--------
(= (select src i) 0);
 (< x i);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- x 1)),(distinct (select src _i0) 0)} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(distinct (select dst _i0) 0)} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(= (select dst _i0) (select src _i0))} || {(= x 0)};
 forall _i0 in [0,1,x],(distinct (select src _i0) 0);
 forall _i0 in [0,1,x],(distinct (select dst _i0) 0);
 forall _i0 in [0,1,x],(= (select dst _i0) (select src _i0));
 
----------[B2]-> [B3] out -------:
(= (select src i) 0);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0))} || {(= i 0)};
 forall _i0 in [0,1,(- x 1)),(distinct (select src _i0) 0);
 forall _i0 in [0,1,(- x 1)),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,(- x 1)),(= (select dst _i0) (select src _i0));
 
--------[B3] in ::--------
(= (select src i) 0);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- x 1)),(distinct (select src _i0) 0)} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(distinct (select dst _i0) 0)} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(= (select dst _i0) (select src _i0))} || {(= x 0)};
 
----------[B3]-> [B2] out -------:
(= (select src i) 0);
 (< x i);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- x 1)),(distinct (select src _i0) 0)} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(distinct (select dst _i0) 0)} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(= (select dst _i0) (select src _i0))} || {(= x 0)};
 forall _i0 in [0,1,x],(distinct (select src _i0) 0);
 forall _i0 in [0,1,x],(distinct (select dst _i0) 0);
 forall _i0 in [0,1,x],(= (select dst _i0) (select src _i0));
 
----------[B3]-> [B1] out -------:
(= (select src i) 0);
 (>= x i);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- x 1)),(distinct (select src _i0) 0)} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(distinct (select dst _i0) 0)} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(= (select dst _i0) (select src _i0))} || {(= x 0)};
 exist _i0 in [0,1,x],(= (select src _i0) 0);
 
--------[B4] in ::--------
(= (select src i) 0);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0))} || {(= i 0)};
 
----------[B4]-> [B3] out -------:
(= (select src i) 0);
 (= x 0);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0))} || {(= i 0)};
 
--------[B5] in ::--------
forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0);
 forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0));
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 
----------[B5]-> [B7] out -------:
forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0);
 forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0));
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 
--------[B6] in ::--------
(distinct (select src i) 0);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0))} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),(distinct (select src _i0) 0);
 
----------[B6]-> [B5] out -------:
forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0);
 forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0));
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 
--------[B7] in ::--------
forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0))} || {(= i 0)};
 
----------[B7]-> [B6] out -------:
(distinct (select src i) 0);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0))} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),(distinct (select src _i0) 0);
 
----------[B7]-> [B4] out -------:
(= (select src i) 0);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0))} || {(= i 0)};
 
--------[B8] in ::--------

----------[B8]-> [B7] out -------:
(= i 0);
 
--------[B9] in ::--------

----------[B9]-> [B8] out -------:

