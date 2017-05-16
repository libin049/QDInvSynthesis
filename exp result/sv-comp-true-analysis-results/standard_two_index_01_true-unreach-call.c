*******************process function::  main***************
--------[B0] in ::--------
(>= i 10000);
 (= _ret 0);
 exist _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 
--------[B1] in ::--------
(>= i 10000);
 exist _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 
----------[B1]-> [B0] out -------:
(>= i 10000);
 (= _ret 0);
 exist _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 
--------[B2] in ::--------
exist _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 
----------[B2]-> [B4] out -------:
exist _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 
--------[B3] in ::--------
(< i 10000);
 exist _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 
----------[B3]-> [B2] out -------:
exist _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 
--------[B4] in ::--------
exist _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 
----------[B4]-> [B3] out -------:
(< i 10000);
 exist _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 
----------[B4]-> [B1] out -------:
(>= i 10000);
 exist _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 
--------[B5] in ::--------
(>= i 10000);
 exist _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,i),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,(- j 1)),(= (select a _i0) (select b _i0));
 forall _i1 in [0,1,(- j 1)),exist _i0 in [0,1,10000),(= (select a _i1) (select b _i0));
 forall _i0 in [0,1,j),(= (select a _i0) (select b _i0));
 forall _i1 in [0,1,j),exist _i0 in [0,1,10000),(= (select a _i1) (select b _i0));
 forall _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 
----------[B5]-> [B4] out -------:
(= i 0);
 (= j 0);
 exist _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 
--------[B6] in ::--------
exist _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,i),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,(- j 1)),(= (select a _i0) (select b _i0));
 forall _i1 in [0,1,(- j 1)),exist _i0 in [0,1,10000),(= (select a _i1) (select b _i0));
 forall _i0 in [0,1,j),(= (select a _i0) (select b _i0));
 forall _i1 in [0,1,j),exist _i0 in [0,1,10000),(= (select a _i1) (select b _i0));
 
----------[B6]-> [B8] out -------:
exist _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,i),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,(- j 1)),(= (select a _i0) (select b _i0));
 forall _i1 in [0,1,(- j 1)),exist _i0 in [0,1,10000),(= (select a _i1) (select b _i0));
 forall _i0 in [0,1,j),(= (select a _i0) (select b _i0));
 forall _i1 in [0,1,j),exist _i0 in [0,1,10000),(= (select a _i1) (select b _i0));
 
--------[B7] in ::--------
(< i 10000);
 forall _i0 in [0,1,i),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,j),(= (select a _i0) (select b _i0));
 forall _i1 in [0,1,j),exist _i0 in [0,1,10000),(= (select a _i1) (select b _i0));
 {exist _i0 in [0,1,10000),(= (select a _i0) (select b _i0))} || {(= i 0)};
 {exist _i0 in [0,1,10000),(= (select a _i0) (select b _i0))} || {(= j 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0))} || {(= j 0)};
 {forall _i0 in [0,1,(- j 1)),(= (select a _i0) (select b _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- j 1)),(= (select a _i0) (select b _i0))} || {(= j 0)};
 {forall _i1 in [0,1,(- j 1)),exist _i0 in [0,1,10000),(= (select a _i1) (select b _i0))} || {(= i 0)};
 {forall _i1 in [0,1,(- j 1)),exist _i0 in [0,1,10000),(= (select a _i1) (select b _i0))} || {(= j 0)};
 
----------[B7]-> [B6] out -------:
exist _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,i),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,(- j 1)),(= (select a _i0) (select b _i0));
 forall _i1 in [0,1,(- j 1)),exist _i0 in [0,1,10000),(= (select a _i1) (select b _i0));
 forall _i0 in [0,1,j),(= (select a _i0) (select b _i0));
 forall _i1 in [0,1,j),exist _i0 in [0,1,10000),(= (select a _i1) (select b _i0));
 
--------[B8] in ::--------
forall _i0 in [0,1,i),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,j),(= (select a _i0) (select b _i0));
 forall _i1 in [0,1,j),exist _i0 in [0,1,10000),(= (select a _i1) (select b _i0));
 {exist _i0 in [0,1,10000),(= (select a _i0) (select b _i0))} || {(= i 0)};
 {exist _i0 in [0,1,10000),(= (select a _i0) (select b _i0))} || {(= j 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0))} || {(= j 0)};
 {forall _i0 in [0,1,(- j 1)),(= (select a _i0) (select b _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- j 1)),(= (select a _i0) (select b _i0))} || {(= j 0)};
 {forall _i1 in [0,1,(- j 1)),exist _i0 in [0,1,10000),(= (select a _i1) (select b _i0))} || {(= i 0)};
 {forall _i1 in [0,1,(- j 1)),exist _i0 in [0,1,10000),(= (select a _i1) (select b _i0))} || {(= j 0)};
 
----------[B8]-> [B7] out -------:
(< i 10000);
 forall _i0 in [0,1,i),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,j),(= (select a _i0) (select b _i0));
 forall _i1 in [0,1,j),exist _i0 in [0,1,10000),(= (select a _i1) (select b _i0));
 {exist _i0 in [0,1,10000),(= (select a _i0) (select b _i0))} || {(= i 0)};
 {exist _i0 in [0,1,10000),(= (select a _i0) (select b _i0))} || {(= j 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0))} || {(= j 0)};
 {forall _i0 in [0,1,(- j 1)),(= (select a _i0) (select b _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- j 1)),(= (select a _i0) (select b _i0))} || {(= j 0)};
 {forall _i1 in [0,1,(- j 1)),exist _i0 in [0,1,10000),(= (select a _i1) (select b _i0))} || {(= i 0)};
 {forall _i1 in [0,1,(- j 1)),exist _i0 in [0,1,10000),(= (select a _i1) (select b _i0))} || {(= j 0)};
 
----------[B8]-> [B5] out -------:
(>= i 10000);
 exist _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,i),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,(- j 1)),(= (select a _i0) (select b _i0));
 forall _i1 in [0,1,(- j 1)),exist _i0 in [0,1,10000),(= (select a _i1) (select b _i0));
 forall _i0 in [0,1,j),(= (select a _i0) (select b _i0));
 forall _i1 in [0,1,j),exist _i0 in [0,1,10000),(= (select a _i1) (select b _i0));
 forall _i0 in [0,1,10000),(= (select a _i0) (select b _i0));
 
--------[B9] in ::--------

----------[B9]-> [B8] out -------:
(= i 0);
 (= j 0);
 
--------[B10] in ::--------

----------[B10]-> [B9] out -------:

