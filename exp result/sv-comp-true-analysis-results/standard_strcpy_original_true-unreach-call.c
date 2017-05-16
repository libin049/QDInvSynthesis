*******************process function::  main***************
--------[B0] in ::--------
(= (select src i) 0);
 (= _ret 0);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 
--------[B1] in ::--------
(= (select src i) 0);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 
----------[B1]-> [B0] out -------:
(= (select src i) 0);
 (= _ret 0);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 
--------[B2] in ::--------
forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 
----------[B2]-> [B4] out -------:
forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 
--------[B3] in ::--------
(distinct (select src i) 0);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),(distinct (select src _i0) 0);
 
----------[B3]-> [B2] out -------:
forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 
--------[B4] in ::--------
forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 
----------[B4]-> [B3] out -------:
(distinct (select src i) 0);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),(distinct (select src _i0) 0);
 
----------[B4]-> [B1] out -------:
(= (select src i) 0);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 
--------[B5] in ::--------
(= (select src i) 0);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0))} || {(= i 0)};
 
----------[B5]-> [B4] out -------:
(= i 0);
 
--------[B6] in ::--------
forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0);
 forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0));
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 
----------[B6]-> [B8] out -------:
forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0);
 forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0));
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 
--------[B7] in ::--------
(distinct (select src i) 0);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0))} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),(distinct (select src _i0) 0);
 
----------[B7]-> [B6] out -------:
forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0);
 forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0));
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 
--------[B8] in ::--------
forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0))} || {(= i 0)};
 
----------[B8]-> [B7] out -------:
(distinct (select src i) 0);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0))} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),(distinct (select src _i0) 0);
 
----------[B8]-> [B5] out -------:
(= (select src i) 0);
 forall _i0 in [0,1,i),(distinct (select src _i0) 0);
 forall _i0 in [0,1,i),(distinct (select dst _i0) 0);
 forall _i0 in [0,1,i),(= (select dst _i0) (select src _i0));
 {forall _i0 in [0,1,(- i 1)),(distinct (select src _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select dst _i0) 0)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select dst _i0) (select src _i0))} || {(= i 0)};
 
--------[B9] in ::--------

----------[B9]-> [B8] out -------:
(= i 0);
 
--------[B10] in ::--------

----------[B10]-> [B9] out -------:

