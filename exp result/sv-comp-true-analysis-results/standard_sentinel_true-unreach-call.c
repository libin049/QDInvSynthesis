*******************process function::  main***************
--------[B0] in ::--------
(= _ret 0);
 {(>= pos 0)} || {(< pos 0)};
 
--------[B1] in ::--------
{(>= pos 0)} || {(< pos 0)};
 
----------[B1]-> [B0] out -------:
(= _ret 0);
 {(>= pos 0)} || {(< pos 0)};
 
--------[B2] in ::--------
(>= pos 0);
 (< 0 100000);
 (< pos 100000);
 (= (select a pos) marker);
 forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) (select a pos));
 forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) marker);
 forall _i0 in [0,1,i),(distinct (select a _i0) (select a pos));
 forall _i0 in [0,1,i),(distinct (select a _i0) marker);
 
----------[B2]-> [B4] out -------:
(>= pos 0);
 (< 0 100000);
 (< pos 100000);
 (= (select a pos) marker);
 forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) (select a pos));
 forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) marker);
 forall _i0 in [0,1,i),(distinct (select a _i0) (select a pos));
 forall _i0 in [0,1,i),(distinct (select a _i0) marker);
 
--------[B3] in ::--------
(>= pos 0);
 (< 0 100000);
 (< pos 100000);
 (= (select a pos) marker);
 (distinct (select a i) (select a pos));
 (distinct (select a i) marker);
 forall _i0 in [0,1,i),(distinct (select a _i0) (select a pos));
 forall _i0 in [0,1,i),(distinct (select a _i0) marker);
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) (select a pos))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) marker)} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),(distinct (select a _i0) (select a pos));
 forall _i0 in [0,1,(+ i 1)),(distinct (select a _i0) marker);
 
----------[B3]-> [B2] out -------:
(>= pos 0);
 (< 0 100000);
 (< pos 100000);
 (= (select a pos) marker);
 forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) (select a pos));
 forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) marker);
 forall _i0 in [0,1,i),(distinct (select a _i0) (select a pos));
 forall _i0 in [0,1,i),(distinct (select a _i0) marker);
 
--------[B4] in ::--------
(>= pos 0);
 (< 0 100000);
 (< pos 100000);
 (= (select a pos) marker);
 forall _i0 in [0,1,i),(distinct (select a _i0) (select a pos));
 forall _i0 in [0,1,i),(distinct (select a _i0) marker);
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) (select a pos))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) marker)} || {(= i 0)};
 
----------[B4]-> [B3] out -------:
(>= pos 0);
 (< 0 100000);
 (< pos 100000);
 (= (select a pos) marker);
 (distinct (select a i) (select a pos));
 (distinct (select a i) marker);
 forall _i0 in [0,1,i),(distinct (select a _i0) (select a pos));
 forall _i0 in [0,1,i),(distinct (select a _i0) marker);
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) (select a pos))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) marker)} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),(distinct (select a _i0) (select a pos));
 forall _i0 in [0,1,(+ i 1)),(distinct (select a _i0) marker);
 
----------[B4]-> [B1] out -------:
(>= pos 0);
 (< 0 100000);
 (< pos 100000);
 (= (select a pos) marker);
 (= (select a pos) (select a i));
 (= (select a i) marker);
 forall _i0 in [0,1,i),(distinct (select a _i0) (select a pos));
 forall _i0 in [0,1,i),(distinct (select a _i0) marker);
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) (select a pos))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) marker)} || {(= i 0)};
 forall _i0 in [0,1,i),(distinct (select a _i0) (select a i));
 
--------[B5] in ::--------
(>= pos 0);
 (< 0 100000);
 (< pos 100000);
 
----------[B5]-> [B4] out -------:
(>= pos 0);
 (< 0 100000);
 (< pos 100000);
 (= (select a pos) marker);
 (= i 0);
 
--------[B6] in ::--------
(>= pos 0);
 
----------[B6]-> [B5] out -------:
(>= pos 0);
 (< 0 100000);
 (< pos 100000);
 
----------[B6]-> [B1] out -------:
(>= pos 0);
 (>= pos 100000);
 
--------[B7] in ::--------

----------[B7]-> [B6] out -------:
(>= pos 0);
 
----------[B7]-> [B1] out -------:
(< pos 0);
 
--------[B8] in ::--------

----------[B8]-> [B7] out -------:

