*******************process function::  main***************
--------[B0] in ::--------
(>= i 100000);
 (>= x 100000);
 (= _ret 0);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 forall _i0 in [0,1,(- x 1)),(= (select a _i0) 42);
 
--------[B1] in ::--------
(>= i 100000);
 (>= x 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 forall _i0 in [0,1,(- x 1)),(= (select a _i0) 42);
 
----------[B1]-> [B0] out -------:
(>= i 100000);
 (>= x 100000);
 (= _ret 0);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 forall _i0 in [0,1,(- x 1)),(= (select a _i0) 42);
 
--------[B2] in ::--------
(>= i 100000);
 (< x i);
 (< x 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 {forall _i0 in [0,1,(- x 1)),(= (select a _i0) 42)} || {(= x 0)};
 forall _i0 in [0,1,x],(= (select a _i0) 42);
 
----------[B2]-> [B3] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 forall _i0 in [0,1,(- x 1)),(= (select a _i0) 42);
 
--------[B3] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 {forall _i0 in [0,1,(- x 1)),(= (select a _i0) 42)} || {(= x 0)};
 
----------[B3]-> [B2] out -------:
(>= i 100000);
 (< x i);
 (< x 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 {forall _i0 in [0,1,(- x 1)),(= (select a _i0) 42)} || {(= x 0)};
 forall _i0 in [0,1,x],(= (select a _i0) 42);
 
----------[B3]-> [B1] out -------:
(>= i 100000);
 (>= x 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 forall _i0 in [0,1,(- x 1)),(= (select a _i0) 42);
 
--------[B4] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 
----------[B4]-> [B3] out -------:
(>= i 100000);
 (= x 0);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 
--------[B5] in ::--------
(< i 100000);
 (= (select a i) 42);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42)} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),(= (select a _i0) 42);
 
----------[B5]-> [B7] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 
--------[B6] in ::--------
(< i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42)} || {(= i 0)};
 
----------[B6]-> [B5] out -------:
(< i 100000);
 (= (select a i) 42);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42)} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),(= (select a _i0) 42);
 
--------[B7] in ::--------
exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42)} || {(= i 0)};
 
----------[B7]-> [B6] out -------:
(< i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42)} || {(= i 0)};
 
----------[B7]-> [B4] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 
--------[B8] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 
----------[B8]-> [B7] out -------:
(= i 0);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 
--------[B9] in ::--------
(< i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 
----------[B9]-> [B11] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 
--------[B10] in ::--------
(< i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 
----------[B10]-> [B9] out -------:
(< i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 
--------[B11] in ::--------
exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 
----------[B11]-> [B10] out -------:
(< i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 
----------[B11]-> [B8] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 
--------[B12] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select b _i0) 42);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 exist _i0 in [0,1,100000),(= (select b _i0) (select a _i0));
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select b _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select b _i0) (select a _i0));
 forall _i0 in [0,1,i),(= (select b _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select b _i0) (select a _i0));
 forall _i0 in [0,1,100000),(= (select b _i0) 42);
 forall _i0 in [0,1,100000),(= (select b _i0) (select a _i0));
 
----------[B12]-> [B11] out -------:
(= i 0);
 exist _i0 in [0,1,100000),(= (select b _i0) 42);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 exist _i0 in [0,1,100000),(= (select b _i0) (select a _i0));
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select b _i0) 42);
 forall _i0 in [0,1,100000),(= (select b _i0) (select a _i0));
 
--------[B13] in ::--------
(= (select b i) 42);
 (< i 100000);
 (= (select a i) 42);
 (= (select b i) (select a i));
 exist _i0 in [0,1,100000),(= (select b _i0) 42);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 exist _i0 in [0,1,100000),(= (select b _i0) (select a _i0));
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select b _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select b _i0) (select a _i0));
 {forall _i0 in [0,1,(- i 1)),(= (select b _i0) 42)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select b _i0) (select a _i0))} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),(= (select b _i0) 42);
 forall _i0 in [0,1,(+ i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,(+ i 1)),(= (select b _i0) (select a _i0));
 
----------[B13]-> [B15] out -------:
exist _i0 in [0,1,100000),(= (select b _i0) 42);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 exist _i0 in [0,1,100000),(= (select b _i0) (select a _i0));
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select b _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select b _i0) (select a _i0));
 forall _i0 in [0,1,i),(= (select b _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select b _i0) (select a _i0));
 
--------[B14] in ::--------
(< i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select b _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select b _i0) (select a _i0));
 {exist _i0 in [0,1,100000),(= (select b _i0) 42)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) (select a _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select b _i0) 42)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select b _i0) (select a _i0))} || {(= i 0)};
 
----------[B14]-> [B13] out -------:
(= (select b i) 42);
 (< i 100000);
 (= (select a i) 42);
 (= (select b i) (select a i));
 exist _i0 in [0,1,100000),(= (select b _i0) 42);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 exist _i0 in [0,1,100000),(= (select b _i0) (select a _i0));
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select b _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select b _i0) (select a _i0));
 {forall _i0 in [0,1,(- i 1)),(= (select b _i0) 42)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select b _i0) (select a _i0))} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),(= (select b _i0) 42);
 forall _i0 in [0,1,(+ i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,(+ i 1)),(= (select b _i0) (select a _i0));
 
--------[B15] in ::--------
exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select b _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select b _i0) (select a _i0));
 {exist _i0 in [0,1,100000),(= (select b _i0) 42)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) (select a _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select b _i0) 42)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select b _i0) (select a _i0))} || {(= i 0)};
 
----------[B15]-> [B14] out -------:
(< i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select b _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select b _i0) (select a _i0));
 {exist _i0 in [0,1,100000),(= (select b _i0) 42)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) (select a _i0))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select b _i0) 42)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select b _i0) (select a _i0))} || {(= i 0)};
 
----------[B15]-> [B12] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select b _i0) 42);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 exist _i0 in [0,1,100000),(= (select b _i0) (select a _i0));
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select b _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select b _i0) (select a _i0));
 forall _i0 in [0,1,i),(= (select b _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select b _i0) (select a _i0));
 forall _i0 in [0,1,100000),(= (select b _i0) 42);
 forall _i0 in [0,1,100000),(= (select b _i0) (select a _i0));
 
--------[B16] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 
----------[B16]-> [B15] out -------:
(= i 0);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 
--------[B17] in ::--------
exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 
----------[B17]-> [B19] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 
--------[B18] in ::--------
(< i 100000);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 {exist _i0 in [0,1,100000),(= (select a _i0) 42)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42)} || {(= i 0)};
 
----------[B18]-> [B17] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 
--------[B19] in ::--------
forall _i0 in [0,1,i),(= (select a _i0) 42);
 {exist _i0 in [0,1,100000),(= (select a _i0) 42)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42)} || {(= i 0)};
 
----------[B19]-> [B18] out -------:
(< i 100000);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 {exist _i0 in [0,1,100000),(= (select a _i0) 42)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42)} || {(= i 0)};
 
----------[B19]-> [B16] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 
--------[B20] in ::--------

----------[B20]-> [B19] out -------:
(= i 0);
 
--------[B21] in ::--------

----------[B21]-> [B20] out -------:

