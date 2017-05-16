*******************process function::  incrementArray***************
--------[B0] in ::--------
(>= i 100000);
 
--------[B1] in ::--------
(< i 100000);
 
----------[B1]-> [B3] out -------:

--------[B2] in ::--------
(< i 100000);
 
----------[B2]-> [B1] out -------:
(< i 100000);
 
--------[B3] in ::--------

----------[B3]-> [B2] out -------:
(< i 100000);
 
----------[B3]-> [B0] out -------:
(>= i 100000);
 
--------[B4] in ::--------

----------[B4]-> [B3] out -------:
(= i 0);
 
--------[B5] in ::--------

----------[B5]-> [B4] out -------:

*******************process function::  main***************
--------[B0] in ::--------
(>= x 100000);
 (= _ret 0);
 exist _i0 in [0,1,100000),(= (select src _i0) (- (select dst _i0) 1));
 forall _i0 in [0,1,(- x 1)),(= (select src _i0) (- (select dst _i0) 1));
 forall _i0 in [0,1,x),(= (select src _i0) (- (select dst _i0) 1));
 forall _i0 in [0,1,100000),(= (select src _i0) (- (select dst _i0) 1));
 
--------[B1] in ::--------
(>= x 100000);
 exist _i0 in [0,1,100000),(= (select src _i0) (- (select dst _i0) 1));
 forall _i0 in [0,1,(- x 1)),(= (select src _i0) (- (select dst _i0) 1));
 forall _i0 in [0,1,x),(= (select src _i0) (- (select dst _i0) 1));
 forall _i0 in [0,1,100000),(= (select src _i0) (- (select dst _i0) 1));
 
----------[B1]-> [B0] out -------:
(>= x 100000);
 (= _ret 0);
 exist _i0 in [0,1,100000),(= (select src _i0) (- (select dst _i0) 1));
 forall _i0 in [0,1,(- x 1)),(= (select src _i0) (- (select dst _i0) 1));
 forall _i0 in [0,1,x),(= (select src _i0) (- (select dst _i0) 1));
 forall _i0 in [0,1,100000),(= (select src _i0) (- (select dst _i0) 1));
 
--------[B2] in ::--------
(< x 100000);
 (= (select src x) (- (select dst x) 1));
 exist _i0 in [0,1,100000),(= (select src _i0) (- (select dst _i0) 1));
 forall _i0 in [0,1,x),(= (select src _i0) (- (select dst _i0) 1));
 {forall _i0 in [0,1,(- x 1)),(= (select src _i0) (- (select dst _i0) 1))} || {(= x 0)};
 forall _i0 in [0,1,(+ x 1)),(= (select src _i0) (- (select dst _i0) 1));
 
----------[B2]-> [B4] out -------:
exist _i0 in [0,1,100000),(= (select src _i0) (- (select dst _i0) 1));
 forall _i0 in [0,1,(- x 1)),(= (select src _i0) (- (select dst _i0) 1));
 forall _i0 in [0,1,x),(= (select src _i0) (- (select dst _i0) 1));
 
--------[B3] in ::--------
(< x 100000);
 forall _i0 in [0,1,x),(= (select src _i0) (- (select dst _i0) 1));
 {exist _i0 in [0,1,100000),(= (select src _i0) (- (select dst _i0) 1))} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(= (select src _i0) (- (select dst _i0) 1))} || {(= x 0)};
 
----------[B3]-> [B2] out -------:
(< x 100000);
 (= (select src x) (- (select dst x) 1));
 exist _i0 in [0,1,100000),(= (select src _i0) (- (select dst _i0) 1));
 forall _i0 in [0,1,x),(= (select src _i0) (- (select dst _i0) 1));
 {forall _i0 in [0,1,(- x 1)),(= (select src _i0) (- (select dst _i0) 1))} || {(= x 0)};
 forall _i0 in [0,1,(+ x 1)),(= (select src _i0) (- (select dst _i0) 1));
 
--------[B4] in ::--------
forall _i0 in [0,1,x),(= (select src _i0) (- (select dst _i0) 1));
 {exist _i0 in [0,1,100000),(= (select src _i0) (- (select dst _i0) 1))} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(= (select src _i0) (- (select dst _i0) 1))} || {(= x 0)};
 
----------[B4]-> [B3] out -------:
(< x 100000);
 forall _i0 in [0,1,x),(= (select src _i0) (- (select dst _i0) 1));
 {exist _i0 in [0,1,100000),(= (select src _i0) (- (select dst _i0) 1))} || {(= x 0)};
 {forall _i0 in [0,1,(- x 1)),(= (select src _i0) (- (select dst _i0) 1))} || {(= x 0)};
 
----------[B4]-> [B1] out -------:
(>= x 100000);
 exist _i0 in [0,1,100000),(= (select src _i0) (- (select dst _i0) 1));
 forall _i0 in [0,1,(- x 1)),(= (select src _i0) (- (select dst _i0) 1));
 forall _i0 in [0,1,x),(= (select src _i0) (- (select dst _i0) 1));
 forall _i0 in [0,1,100000),(= (select src _i0) (- (select dst _i0) 1));
 
--------[B5] in ::--------

----------[B5]-> [B4] out -------:
(= x 0);
 
--------[B6] in ::--------

----------[B6]-> [B5] out -------:

