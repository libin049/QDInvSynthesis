*******************process function::  main***************
--------[B0] in ::--------
(< (select aa a) 0);
 (>= x a);
 (= _ret 0);
 exist _i0 in [0,1,x],(< (select aa _i0) 0);
 forall _i0 in [0,1,a),(>= (select aa _i0) 0);
 {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)} || {(= a 0)};
 {forall _i0 in [0,1,(- x 1)),(>= (select aa _i0) 0)} || {(= x 0)};
 
--------[B1] in ::--------
(< (select aa a) 0);
 (>= x a);
 forall _i0 in [0,1,a),(>= (select aa _i0) 0);
 {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)} || {(= a 0)};
 {forall _i0 in [0,1,(- x 1)),(>= (select aa _i0) 0)} || {(= x 0)};
 exist _i0 in [0,1,x],(< (select aa _i0) 0);
 
----------[B1]-> [B0] out -------:
(< (select aa a) 0);
 (>= x a);
 (= _ret 0);
 exist _i0 in [0,1,x],(< (select aa _i0) 0);
 forall _i0 in [0,1,a),(>= (select aa _i0) 0);
 {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)} || {(= a 0)};
 {forall _i0 in [0,1,(- x 1)),(>= (select aa _i0) 0)} || {(= x 0)};
 
--------[B2] in ::--------
(< (select aa a) 0);
 (< x a);
 forall _i0 in [0,1,a),(>= (select aa _i0) 0);
 {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)} || {(= a 0)};
 {forall _i0 in [0,1,(- x 1)),(>= (select aa _i0) 0)} || {(= x 0)};
 forall _i0 in [0,1,x],(>= (select aa _i0) 0);
 
----------[B2]-> [B3] out -------:
(< (select aa a) 0);
 forall _i0 in [0,1,a),(>= (select aa _i0) 0);
 {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)} || {(= a 0)};
 forall _i0 in [0,1,(- x 1)),(>= (select aa _i0) 0);
 
--------[B3] in ::--------
(< (select aa a) 0);
 forall _i0 in [0,1,a),(>= (select aa _i0) 0);
 {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)} || {(= a 0)};
 {forall _i0 in [0,1,(- x 1)),(>= (select aa _i0) 0)} || {(= x 0)};
 
----------[B3]-> [B2] out -------:
(< (select aa a) 0);
 (< x a);
 forall _i0 in [0,1,a),(>= (select aa _i0) 0);
 {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)} || {(= a 0)};
 {forall _i0 in [0,1,(- x 1)),(>= (select aa _i0) 0)} || {(= x 0)};
 forall _i0 in [0,1,x],(>= (select aa _i0) 0);
 
----------[B3]-> [B1] out -------:
(< (select aa a) 0);
 (>= x a);
 forall _i0 in [0,1,a),(>= (select aa _i0) 0);
 {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)} || {(= a 0)};
 {forall _i0 in [0,1,(- x 1)),(>= (select aa _i0) 0)} || {(= x 0)};
 exist _i0 in [0,1,x],(< (select aa _i0) 0);
 
--------[B4] in ::--------
(< (select aa a) 0);
 forall _i0 in [0,1,a),(>= (select aa _i0) 0);
 {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)} || {(= a 0)};
 
----------[B4]-> [B3] out -------:
(< (select aa a) 0);
 (= x 0);
 forall _i0 in [0,1,a),(>= (select aa _i0) 0);
 {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)} || {(= a 0)};
 
--------[B5] in ::--------
forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0);
 forall _i0 in [0,1,a),(>= (select aa _i0) 0);
 
----------[B5]-> [B7] out -------:
forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0);
 forall _i0 in [0,1,a),(>= (select aa _i0) 0);
 
--------[B6] in ::--------
(>= (select aa a) 0);
 forall _i0 in [0,1,a),(>= (select aa _i0) 0);
 {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)} || {(= a 0)};
 forall _i0 in [0,1,(+ a 1)),(>= (select aa _i0) 0);
 
----------[B6]-> [B5] out -------:
forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0);
 forall _i0 in [0,1,a),(>= (select aa _i0) 0);
 
--------[B7] in ::--------
forall _i0 in [0,1,a),(>= (select aa _i0) 0);
 {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)} || {(= a 0)};
 
----------[B7]-> [B6] out -------:
(>= (select aa a) 0);
 forall _i0 in [0,1,a),(>= (select aa _i0) 0);
 {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)} || {(= a 0)};
 forall _i0 in [0,1,(+ a 1)),(>= (select aa _i0) 0);
 
----------[B7]-> [B4] out -------:
(< (select aa a) 0);
 forall _i0 in [0,1,a),(>= (select aa _i0) 0);
 {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)} || {(= a 0)};
 
--------[B8] in ::--------

----------[B8]-> [B7] out -------:
(= a 0);
 
--------[B9] in ::--------

----------[B9]-> [B8] out -------:

