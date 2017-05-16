*******************process function::  main***************
--------[B0] in ::--------
(>= i 100000);
 (>= x 100000);
 (= _ret 0);
 exist _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 forall _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- x 1)),(= (select a _i0) 43);
 
--------[B1] in ::--------
(>= i 100000);
 (>= x 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 forall _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- x 1)),(= (select a _i0) 43);
 
----------[B1]-> [B0] out -------:
(>= i 100000);
 (>= x 100000);
 (= _ret 0);
 exist _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 forall _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- x 1)),(= (select a _i0) 43);
 
--------[B2] in ::--------
(>= i 100000);
 (< x i);
 (< x 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 forall _i0 in [0,1,100000),(= (select a _i0) 43);
 {forall _i0 in [0,1,(- x 1)),(= (select a _i0) 43)} || {(= x 0)};
 forall _i0 in [0,1,x],(= (select a _i0) 43);
 
----------[B2]-> [B3] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 forall _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- x 1)),(= (select a _i0) 43);
 
--------[B3] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 forall _i0 in [0,1,100000),(= (select a _i0) 43);
 {forall _i0 in [0,1,(- x 1)),(= (select a _i0) 43)} || {(= x 0)};
 
----------[B3]-> [B2] out -------:
(>= i 100000);
 (< x i);
 (< x 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 forall _i0 in [0,1,100000),(= (select a _i0) 43);
 {forall _i0 in [0,1,(- x 1)),(= (select a _i0) 43)} || {(= x 0)};
 forall _i0 in [0,1,x],(= (select a _i0) 43);
 
----------[B3]-> [B1] out -------:
(>= i 100000);
 (>= x 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 forall _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- x 1)),(= (select a _i0) 43);
 
--------[B4] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 forall _i0 in [0,1,100000),(= (select a _i0) 43);
 
----------[B4]-> [B3] out -------:
(>= i 100000);
 (= x 0);
 exist _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 forall _i0 in [0,1,100000),(= (select a _i0) 43);
 
--------[B5] in ::--------
exist _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 
----------[B5]-> [B7] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 
--------[B6] in ::--------
(< i 100000);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 {exist _i0 in [0,1,100000),(= (select a _i0) 43)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 43)} || {exist _i0 in [0,1,100000),(= (select a _i0) 42)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 43)} || {forall _i0 in [0,1,100000),(= (select a _i0) 42)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43)} || {exist _i0 in [0,1,100000),(= (select a _i0) 42)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43)} || {forall _i0 in [0,1,100000),(= (select a _i0) 42)};
 
----------[B6]-> [B5] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 
--------[B7] in ::--------
forall _i0 in [0,1,i),(= (select a _i0) 43);
 {exist _i0 in [0,1,100000),(= (select a _i0) 43)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 43)} || {exist _i0 in [0,1,100000),(= (select a _i0) 42)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 43)} || {forall _i0 in [0,1,100000),(= (select a _i0) 42)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43)} || {exist _i0 in [0,1,100000),(= (select a _i0) 42)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43)} || {forall _i0 in [0,1,100000),(= (select a _i0) 42)};
 
----------[B7]-> [B6] out -------:
(< i 100000);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 {exist _i0 in [0,1,100000),(= (select a _i0) 43)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 43)} || {exist _i0 in [0,1,100000),(= (select a _i0) 42)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 43)} || {forall _i0 in [0,1,100000),(= (select a _i0) 42)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43)} || {exist _i0 in [0,1,100000),(= (select a _i0) 42)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43)} || {forall _i0 in [0,1,100000),(= (select a _i0) 42)};
 
----------[B7]-> [B4] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 forall _i0 in [0,1,100000),(= (select a _i0) 43);
 
--------[B8] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 
----------[B8]-> [B7] out -------:
(= i 0);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 
--------[B9] in ::--------
exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 
----------[B9]-> [B11] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 
--------[B10] in ::--------
(< i 100000);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 {exist _i0 in [0,1,100000),(= (select a _i0) 42)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42)} || {(= i 0)};
 
----------[B10]-> [B9] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 
--------[B11] in ::--------
forall _i0 in [0,1,i),(= (select a _i0) 42);
 {exist _i0 in [0,1,100000),(= (select a _i0) 42)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42)} || {(= i 0)};
 
----------[B11]-> [B10] out -------:
(< i 100000);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 {exist _i0 in [0,1,100000),(= (select a _i0) 42)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42)} || {(= i 0)};
 
----------[B11]-> [B8] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 
--------[B12] in ::--------

----------[B12]-> [B11] out -------:
(= i 0);
 
--------[B13] in ::--------

----------[B13]-> [B12] out -------:

