*******************process function::  strcmp***************
--------[B0] in ::--------
{exist _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(= i 0)};
 forall _i0 in [0,1,i),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 {(>= i 100000)} || {(< i 100000)};
 {(>= i 100000)} || {(distinct (def_pointer (+ dst i)) (def_pointer (+ src i)))};
 {(>= i 100000)} || {(= _ret 1)};
 {(>= i 100000)} || {exist _i0 in [0,1,100000),(distinct (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))};
 {(= _ret 0)} || {(< i 100000)};
 {(= _ret 0)} || {(distinct (def_pointer (+ dst i)) (def_pointer (+ src i)))};
 {(= _ret 0)} || {(= _ret 1)};
 {(= _ret 0)} || {exist _i0 in [0,1,100000),(distinct (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))};
 {exist _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(< i 100000)};
 {exist _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(distinct (def_pointer (+ dst i)) (def_pointer (+ src i)))};
 {exist _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(= _ret 1)};
 {exist _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {exist _i0 in [0,1,100000),(distinct (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))};
 {forall _i0 in [0,1,(- i 1)),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(< i 100000)};
 {forall _i0 in [0,1,(- i 1)),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(distinct (def_pointer (+ dst i)) (def_pointer (+ src i)))};
 {forall _i0 in [0,1,(- i 1)),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(= _ret 1)};
 {forall _i0 in [0,1,(- i 1)),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {exist _i0 in [0,1,100000),(distinct (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))};
 {forall _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(< i 100000)};
 {forall _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(distinct (def_pointer (+ dst i)) (def_pointer (+ src i)))};
 {forall _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(= _ret 1)};
 {forall _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {exist _i0 in [0,1,100000),(distinct (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))};
 
--------[B1] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 forall _i0 in [0,1,(- i 1)),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 forall _i0 in [0,1,i),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 forall _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 
----------[B1]-> [B0] out -------:
(>= i 100000);
 (= _ret 0);
 exist _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 forall _i0 in [0,1,(- i 1)),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 forall _i0 in [0,1,i),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 forall _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 
--------[B2] in ::--------
exist _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 forall _i0 in [0,1,(- i 1)),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 forall _i0 in [0,1,i),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 
----------[B2]-> [B6] out -------:
exist _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 forall _i0 in [0,1,(- i 1)),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 forall _i0 in [0,1,i),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 
--------[B3] in ::--------
(< i 100000);
 (= (def_pointer (+ dst i)) (def_pointer (+ src i)));
 forall _i0 in [0,1,i),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 {forall _i0 in [0,1,(- i 1)),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(= i 0)};
 exist _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 forall _i0 in [0,1,(+ i 1)),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 
----------[B3]-> [B2] out -------:
exist _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 forall _i0 in [0,1,(- i 1)),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 forall _i0 in [0,1,i),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 
--------[B4] in ::--------
(< i 100000);
 (distinct (def_pointer (+ dst i)) (def_pointer (+ src i)));
 forall _i0 in [0,1,i),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 {exist _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(= i 0)};
 exist _i0 in [0,1,100000),(distinct (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 
----------[B4]-> [B0] out -------:
(< i 100000);
 (distinct (def_pointer (+ dst i)) (def_pointer (+ src i)));
 (= _ret 1);
 exist _i0 in [0,1,100000),(distinct (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 forall _i0 in [0,1,i),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 {exist _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(= i 0)};
 
--------[B5] in ::--------
(< i 100000);
 forall _i0 in [0,1,i),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 {exist _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(= i 0)};
 
----------[B5]-> [B4] out -------:
(< i 100000);
 (distinct (def_pointer (+ dst i)) (def_pointer (+ src i)));
 forall _i0 in [0,1,i),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 {exist _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(= i 0)};
 exist _i0 in [0,1,100000),(distinct (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 
----------[B5]-> [B3] out -------:
(< i 100000);
 (= (def_pointer (+ dst i)) (def_pointer (+ src i)));
 forall _i0 in [0,1,i),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 {forall _i0 in [0,1,(- i 1)),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(= i 0)};
 exist _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 forall _i0 in [0,1,(+ i 1)),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 
--------[B6] in ::--------
forall _i0 in [0,1,i),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 {exist _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(= i 0)};
 
----------[B6]-> [B5] out -------:
(< i 100000);
 forall _i0 in [0,1,i),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 {exist _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)))} || {(= i 0)};
 
----------[B6]-> [B1] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 forall _i0 in [0,1,(- i 1)),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 forall _i0 in [0,1,i),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 forall _i0 in [0,1,100000),(= (def_pointer (+ dst _i0)) (def_pointer (+ src _i0)));
 
--------[B7] in ::--------

----------[B7]-> [B6] out -------:
(= i 0);
 
--------[B8] in ::--------

----------[B8]-> [B7] out -------:

*******************process function::  main***************
--------[B0] in ::--------
(= c (strcmp a b));
 (= _ret 0);
 {(= c 0)} || {(not (= c 0))};
 {(>= x 100000)} || {(not (= c 0))};
 
--------[B1] in ::--------
(= c (strcmp a b));
 {(= c 0)} || {(not (= c 0))};
 {(>= x 100000)} || {(not (= c 0))};
 
----------[B1]-> [B0] out -------:
(= c (strcmp a b));
 (= _ret 0);
 {(= c 0)} || {(not (= c 0))};
 {(>= x 100000)} || {(not (= c 0))};
 
--------[B2] in ::--------
(= c (strcmp a b));
 (= c 0);
 (< x 100000);
 
----------[B2]-> [B3] out -------:
(= c (strcmp a b));
 (= c 0);
 
--------[B3] in ::--------
(= c (strcmp a b));
 (= c 0);
 
----------[B3]-> [B2] out -------:
(= c (strcmp a b));
 (= c 0);
 (< x 100000);
 
----------[B3]-> [B1] out -------:
(= c (strcmp a b));
 (= c 0);
 (>= x 100000);
 
--------[B4] in ::--------
(= c (strcmp a b));
 (= c 0);
 
----------[B4]-> [B3] out -------:
(= c (strcmp a b));
 (= c 0);
 (= x 0);
 
--------[B5] in ::--------

----------[B5]-> [B4] out -------:
(= c (strcmp a b));
 (= c 0);
 
----------[B5]-> [B1] out -------:
(= c (strcmp a b));
 (not (= c 0));
 
--------[B6] in ::--------

----------[B6]-> [B5] out -------:

