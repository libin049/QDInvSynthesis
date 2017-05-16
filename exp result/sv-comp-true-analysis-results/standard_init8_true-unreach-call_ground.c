*******************process function::  main***************
--------[B0] in ::--------
(>= i 100000);
 (>= x 100000);
 (= _ret 0);
 exist _i0 in [0,1,100000),(= (select a _i0) 49);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49);
 forall _i0 in [0,1,i),(= (select a _i0) 49);
 forall _i0 in [0,1,100000),(= (select a _i0) 49);
 forall _i0 in [0,1,(- x 1)),(= (select a _i0) 49);
 
--------[B1] in ::--------
(>= i 100000);
 (>= x 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 49);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49);
 forall _i0 in [0,1,i),(= (select a _i0) 49);
 forall _i0 in [0,1,100000),(= (select a _i0) 49);
 forall _i0 in [0,1,(- x 1)),(= (select a _i0) 49);
 
----------[B1]-> [B0] out -------:
(>= i 100000);
 (>= x 100000);
 (= _ret 0);
 exist _i0 in [0,1,100000),(= (select a _i0) 49);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49);
 forall _i0 in [0,1,i),(= (select a _i0) 49);
 forall _i0 in [0,1,100000),(= (select a _i0) 49);
 forall _i0 in [0,1,(- x 1)),(= (select a _i0) 49);
 
--------[B2] in ::--------
(>= i 100000);
 (< x i);
 (< x 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 49);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49);
 forall _i0 in [0,1,i),(= (select a _i0) 49);
 forall _i0 in [0,1,100000),(= (select a _i0) 49);
 {forall _i0 in [0,1,(- x 1)),(= (select a _i0) 49)} || {(= x 0)};
 forall _i0 in [0,1,x],(= (select a _i0) 49);
 
----------[B2]-> [B3] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 49);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49);
 forall _i0 in [0,1,i),(= (select a _i0) 49);
 forall _i0 in [0,1,100000),(= (select a _i0) 49);
 forall _i0 in [0,1,(- x 1)),(= (select a _i0) 49);
 
--------[B3] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 49);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49);
 forall _i0 in [0,1,i),(= (select a _i0) 49);
 forall _i0 in [0,1,100000),(= (select a _i0) 49);
 {forall _i0 in [0,1,(- x 1)),(= (select a _i0) 49)} || {(= x 0)};
 
----------[B3]-> [B2] out -------:
(>= i 100000);
 (< x i);
 (< x 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 49);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49);
 forall _i0 in [0,1,i),(= (select a _i0) 49);
 forall _i0 in [0,1,100000),(= (select a _i0) 49);
 {forall _i0 in [0,1,(- x 1)),(= (select a _i0) 49)} || {(= x 0)};
 forall _i0 in [0,1,x],(= (select a _i0) 49);
 
----------[B3]-> [B1] out -------:
(>= i 100000);
 (>= x 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 49);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49);
 forall _i0 in [0,1,i),(= (select a _i0) 49);
 forall _i0 in [0,1,100000),(= (select a _i0) 49);
 forall _i0 in [0,1,(- x 1)),(= (select a _i0) 49);
 
--------[B4] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 49);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49);
 forall _i0 in [0,1,i),(= (select a _i0) 49);
 forall _i0 in [0,1,100000),(= (select a _i0) 49);
 
----------[B4]-> [B3] out -------:
(>= i 100000);
 (= x 0);
 exist _i0 in [0,1,100000),(= (select a _i0) 49);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49);
 forall _i0 in [0,1,i),(= (select a _i0) 49);
 forall _i0 in [0,1,100000),(= (select a _i0) 49);
 
--------[B5] in ::--------
exist _i0 in [0,1,100000),(= (select a _i0) 49);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49);
 forall _i0 in [0,1,i),(= (select a _i0) 49);
 
----------[B5]-> [B7] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 49);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49);
 forall _i0 in [0,1,i),(= (select a _i0) 49);
 
--------[B6] in ::--------
(< i 100000);
 forall _i0 in [0,1,i),(= (select a _i0) 49);
 {exist _i0 in [0,1,100000),(= (select a _i0) 49)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 49)} || {exist _i0 in [0,1,100000),(= (select a _i0) 48)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 49)} || {forall _i0 in [0,1,100000),(= (select a _i0) 48)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49)} || {exist _i0 in [0,1,100000),(= (select a _i0) 48)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49)} || {forall _i0 in [0,1,100000),(= (select a _i0) 48)};
 
----------[B6]-> [B5] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 49);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49);
 forall _i0 in [0,1,i),(= (select a _i0) 49);
 
--------[B7] in ::--------
forall _i0 in [0,1,i),(= (select a _i0) 49);
 {exist _i0 in [0,1,100000),(= (select a _i0) 49)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 49)} || {exist _i0 in [0,1,100000),(= (select a _i0) 48)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 49)} || {forall _i0 in [0,1,100000),(= (select a _i0) 48)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49)} || {exist _i0 in [0,1,100000),(= (select a _i0) 48)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49)} || {forall _i0 in [0,1,100000),(= (select a _i0) 48)};
 
----------[B7]-> [B6] out -------:
(< i 100000);
 forall _i0 in [0,1,i),(= (select a _i0) 49);
 {exist _i0 in [0,1,100000),(= (select a _i0) 49)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 49)} || {exist _i0 in [0,1,100000),(= (select a _i0) 48)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 49)} || {forall _i0 in [0,1,100000),(= (select a _i0) 48)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49)} || {exist _i0 in [0,1,100000),(= (select a _i0) 48)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49)} || {forall _i0 in [0,1,100000),(= (select a _i0) 48)};
 
----------[B7]-> [B4] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 49);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 49);
 forall _i0 in [0,1,i),(= (select a _i0) 49);
 forall _i0 in [0,1,100000),(= (select a _i0) 49);
 
--------[B8] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 48);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 48);
 forall _i0 in [0,1,i),(= (select a _i0) 48);
 forall _i0 in [0,1,100000),(= (select a _i0) 48);
 
----------[B8]-> [B7] out -------:
(= i 0);
 exist _i0 in [0,1,100000),(= (select a _i0) 48);
 forall _i0 in [0,1,100000),(= (select a _i0) 48);
 
--------[B9] in ::--------
exist _i0 in [0,1,100000),(= (select a _i0) 48);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 48);
 forall _i0 in [0,1,i),(= (select a _i0) 48);
 
----------[B9]-> [B11] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 48);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 48);
 forall _i0 in [0,1,i),(= (select a _i0) 48);
 
--------[B10] in ::--------
(< i 100000);
 forall _i0 in [0,1,i),(= (select a _i0) 48);
 {exist _i0 in [0,1,100000),(= (select a _i0) 48)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 48)} || {exist _i0 in [0,1,100000),(= (select a _i0) 47)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 48)} || {forall _i0 in [0,1,100000),(= (select a _i0) 47)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 48)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 48)} || {exist _i0 in [0,1,100000),(= (select a _i0) 47)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 48)} || {forall _i0 in [0,1,100000),(= (select a _i0) 47)};
 
----------[B10]-> [B9] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 48);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 48);
 forall _i0 in [0,1,i),(= (select a _i0) 48);
 
--------[B11] in ::--------
forall _i0 in [0,1,i),(= (select a _i0) 48);
 {exist _i0 in [0,1,100000),(= (select a _i0) 48)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 48)} || {exist _i0 in [0,1,100000),(= (select a _i0) 47)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 48)} || {forall _i0 in [0,1,100000),(= (select a _i0) 47)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 48)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 48)} || {exist _i0 in [0,1,100000),(= (select a _i0) 47)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 48)} || {forall _i0 in [0,1,100000),(= (select a _i0) 47)};
 
----------[B11]-> [B10] out -------:
(< i 100000);
 forall _i0 in [0,1,i),(= (select a _i0) 48);
 {exist _i0 in [0,1,100000),(= (select a _i0) 48)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 48)} || {exist _i0 in [0,1,100000),(= (select a _i0) 47)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 48)} || {forall _i0 in [0,1,100000),(= (select a _i0) 47)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 48)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 48)} || {exist _i0 in [0,1,100000),(= (select a _i0) 47)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 48)} || {forall _i0 in [0,1,100000),(= (select a _i0) 47)};
 
----------[B11]-> [B8] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 48);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 48);
 forall _i0 in [0,1,i),(= (select a _i0) 48);
 forall _i0 in [0,1,100000),(= (select a _i0) 48);
 
--------[B12] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 47);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 47);
 forall _i0 in [0,1,i),(= (select a _i0) 47);
 forall _i0 in [0,1,100000),(= (select a _i0) 47);
 
----------[B12]-> [B11] out -------:
(= i 0);
 exist _i0 in [0,1,100000),(= (select a _i0) 47);
 forall _i0 in [0,1,100000),(= (select a _i0) 47);
 
--------[B13] in ::--------
exist _i0 in [0,1,100000),(= (select a _i0) 47);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 47);
 forall _i0 in [0,1,i),(= (select a _i0) 47);
 
----------[B13]-> [B15] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 47);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 47);
 forall _i0 in [0,1,i),(= (select a _i0) 47);
 
--------[B14] in ::--------
(< i 100000);
 forall _i0 in [0,1,i),(= (select a _i0) 47);
 {exist _i0 in [0,1,100000),(= (select a _i0) 47)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 47)} || {exist _i0 in [0,1,100000),(= (select a _i0) 46)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 47)} || {forall _i0 in [0,1,100000),(= (select a _i0) 46)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 47)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 47)} || {exist _i0 in [0,1,100000),(= (select a _i0) 46)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 47)} || {forall _i0 in [0,1,100000),(= (select a _i0) 46)};
 
----------[B14]-> [B13] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 47);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 47);
 forall _i0 in [0,1,i),(= (select a _i0) 47);
 
--------[B15] in ::--------
forall _i0 in [0,1,i),(= (select a _i0) 47);
 {exist _i0 in [0,1,100000),(= (select a _i0) 47)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 47)} || {exist _i0 in [0,1,100000),(= (select a _i0) 46)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 47)} || {forall _i0 in [0,1,100000),(= (select a _i0) 46)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 47)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 47)} || {exist _i0 in [0,1,100000),(= (select a _i0) 46)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 47)} || {forall _i0 in [0,1,100000),(= (select a _i0) 46)};
 
----------[B15]-> [B14] out -------:
(< i 100000);
 forall _i0 in [0,1,i),(= (select a _i0) 47);
 {exist _i0 in [0,1,100000),(= (select a _i0) 47)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 47)} || {exist _i0 in [0,1,100000),(= (select a _i0) 46)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 47)} || {forall _i0 in [0,1,100000),(= (select a _i0) 46)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 47)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 47)} || {exist _i0 in [0,1,100000),(= (select a _i0) 46)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 47)} || {forall _i0 in [0,1,100000),(= (select a _i0) 46)};
 
----------[B15]-> [B12] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 47);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 47);
 forall _i0 in [0,1,i),(= (select a _i0) 47);
 forall _i0 in [0,1,100000),(= (select a _i0) 47);
 
--------[B16] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 46);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 46);
 forall _i0 in [0,1,i),(= (select a _i0) 46);
 forall _i0 in [0,1,100000),(= (select a _i0) 46);
 
----------[B16]-> [B15] out -------:
(= i 0);
 exist _i0 in [0,1,100000),(= (select a _i0) 46);
 forall _i0 in [0,1,100000),(= (select a _i0) 46);
 
--------[B17] in ::--------
exist _i0 in [0,1,100000),(= (select a _i0) 46);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 46);
 forall _i0 in [0,1,i),(= (select a _i0) 46);
 
----------[B17]-> [B19] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 46);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 46);
 forall _i0 in [0,1,i),(= (select a _i0) 46);
 
--------[B18] in ::--------
(< i 100000);
 forall _i0 in [0,1,i),(= (select a _i0) 46);
 {exist _i0 in [0,1,100000),(= (select a _i0) 46)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 46)} || {exist _i0 in [0,1,100000),(= (select a _i0) 45)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 46)} || {forall _i0 in [0,1,100000),(= (select a _i0) 45)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 46)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 46)} || {exist _i0 in [0,1,100000),(= (select a _i0) 45)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 46)} || {forall _i0 in [0,1,100000),(= (select a _i0) 45)};
 
----------[B18]-> [B17] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 46);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 46);
 forall _i0 in [0,1,i),(= (select a _i0) 46);
 
--------[B19] in ::--------
forall _i0 in [0,1,i),(= (select a _i0) 46);
 {exist _i0 in [0,1,100000),(= (select a _i0) 46)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 46)} || {exist _i0 in [0,1,100000),(= (select a _i0) 45)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 46)} || {forall _i0 in [0,1,100000),(= (select a _i0) 45)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 46)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 46)} || {exist _i0 in [0,1,100000),(= (select a _i0) 45)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 46)} || {forall _i0 in [0,1,100000),(= (select a _i0) 45)};
 
----------[B19]-> [B18] out -------:
(< i 100000);
 forall _i0 in [0,1,i),(= (select a _i0) 46);
 {exist _i0 in [0,1,100000),(= (select a _i0) 46)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 46)} || {exist _i0 in [0,1,100000),(= (select a _i0) 45)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 46)} || {forall _i0 in [0,1,100000),(= (select a _i0) 45)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 46)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 46)} || {exist _i0 in [0,1,100000),(= (select a _i0) 45)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 46)} || {forall _i0 in [0,1,100000),(= (select a _i0) 45)};
 
----------[B19]-> [B16] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 46);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 46);
 forall _i0 in [0,1,i),(= (select a _i0) 46);
 forall _i0 in [0,1,100000),(= (select a _i0) 46);
 
--------[B20] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 45);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 45);
 forall _i0 in [0,1,i),(= (select a _i0) 45);
 forall _i0 in [0,1,100000),(= (select a _i0) 45);
 
----------[B20]-> [B19] out -------:
(= i 0);
 exist _i0 in [0,1,100000),(= (select a _i0) 45);
 forall _i0 in [0,1,100000),(= (select a _i0) 45);
 
--------[B21] in ::--------
exist _i0 in [0,1,100000),(= (select a _i0) 45);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 45);
 forall _i0 in [0,1,i),(= (select a _i0) 45);
 
----------[B21]-> [B23] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 45);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 45);
 forall _i0 in [0,1,i),(= (select a _i0) 45);
 
--------[B22] in ::--------
(< i 100000);
 forall _i0 in [0,1,i),(= (select a _i0) 45);
 {exist _i0 in [0,1,100000),(= (select a _i0) 45)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 45)} || {exist _i0 in [0,1,100000),(= (select a _i0) 44)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 45)} || {forall _i0 in [0,1,100000),(= (select a _i0) 44)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 45)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 45)} || {exist _i0 in [0,1,100000),(= (select a _i0) 44)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 45)} || {forall _i0 in [0,1,100000),(= (select a _i0) 44)};
 
----------[B22]-> [B21] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 45);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 45);
 forall _i0 in [0,1,i),(= (select a _i0) 45);
 
--------[B23] in ::--------
forall _i0 in [0,1,i),(= (select a _i0) 45);
 {exist _i0 in [0,1,100000),(= (select a _i0) 45)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 45)} || {exist _i0 in [0,1,100000),(= (select a _i0) 44)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 45)} || {forall _i0 in [0,1,100000),(= (select a _i0) 44)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 45)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 45)} || {exist _i0 in [0,1,100000),(= (select a _i0) 44)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 45)} || {forall _i0 in [0,1,100000),(= (select a _i0) 44)};
 
----------[B23]-> [B22] out -------:
(< i 100000);
 forall _i0 in [0,1,i),(= (select a _i0) 45);
 {exist _i0 in [0,1,100000),(= (select a _i0) 45)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 45)} || {exist _i0 in [0,1,100000),(= (select a _i0) 44)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 45)} || {forall _i0 in [0,1,100000),(= (select a _i0) 44)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 45)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 45)} || {exist _i0 in [0,1,100000),(= (select a _i0) 44)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 45)} || {forall _i0 in [0,1,100000),(= (select a _i0) 44)};
 
----------[B23]-> [B20] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 45);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 45);
 forall _i0 in [0,1,i),(= (select a _i0) 45);
 forall _i0 in [0,1,100000),(= (select a _i0) 45);
 
--------[B24] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 44);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 44);
 forall _i0 in [0,1,i),(= (select a _i0) 44);
 forall _i0 in [0,1,100000),(= (select a _i0) 44);
 
----------[B24]-> [B23] out -------:
(= i 0);
 exist _i0 in [0,1,100000),(= (select a _i0) 44);
 forall _i0 in [0,1,100000),(= (select a _i0) 44);
 
--------[B25] in ::--------
exist _i0 in [0,1,100000),(= (select a _i0) 44);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 44);
 forall _i0 in [0,1,i),(= (select a _i0) 44);
 
----------[B25]-> [B27] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 44);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 44);
 forall _i0 in [0,1,i),(= (select a _i0) 44);
 
--------[B26] in ::--------
(< i 100000);
 forall _i0 in [0,1,i),(= (select a _i0) 44);
 {exist _i0 in [0,1,100000),(= (select a _i0) 44)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 44)} || {exist _i0 in [0,1,100000),(= (select a _i0) 43)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 44)} || {forall _i0 in [0,1,100000),(= (select a _i0) 43)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 44)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 44)} || {exist _i0 in [0,1,100000),(= (select a _i0) 43)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 44)} || {forall _i0 in [0,1,100000),(= (select a _i0) 43)};
 
----------[B26]-> [B25] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 44);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 44);
 forall _i0 in [0,1,i),(= (select a _i0) 44);
 
--------[B27] in ::--------
forall _i0 in [0,1,i),(= (select a _i0) 44);
 {exist _i0 in [0,1,100000),(= (select a _i0) 44)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 44)} || {exist _i0 in [0,1,100000),(= (select a _i0) 43)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 44)} || {forall _i0 in [0,1,100000),(= (select a _i0) 43)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 44)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 44)} || {exist _i0 in [0,1,100000),(= (select a _i0) 43)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 44)} || {forall _i0 in [0,1,100000),(= (select a _i0) 43)};
 
----------[B27]-> [B26] out -------:
(< i 100000);
 forall _i0 in [0,1,i),(= (select a _i0) 44);
 {exist _i0 in [0,1,100000),(= (select a _i0) 44)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 44)} || {exist _i0 in [0,1,100000),(= (select a _i0) 43)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 44)} || {forall _i0 in [0,1,100000),(= (select a _i0) 43)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 44)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 44)} || {exist _i0 in [0,1,100000),(= (select a _i0) 43)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 44)} || {forall _i0 in [0,1,100000),(= (select a _i0) 43)};
 
----------[B27]-> [B24] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 44);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 44);
 forall _i0 in [0,1,i),(= (select a _i0) 44);
 forall _i0 in [0,1,100000),(= (select a _i0) 44);
 
--------[B28] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 forall _i0 in [0,1,100000),(= (select a _i0) 43);
 
----------[B28]-> [B27] out -------:
(= i 0);
 exist _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,100000),(= (select a _i0) 43);
 
--------[B29] in ::--------
exist _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 
----------[B29]-> [B31] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 
--------[B30] in ::--------
(< i 100000);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 {exist _i0 in [0,1,100000),(= (select a _i0) 43)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 43)} || {exist _i0 in [0,1,100000),(= (select a _i0) 42)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 43)} || {forall _i0 in [0,1,100000),(= (select a _i0) 42)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43)} || {exist _i0 in [0,1,100000),(= (select a _i0) 42)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43)} || {forall _i0 in [0,1,100000),(= (select a _i0) 42)};
 
----------[B30]-> [B29] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 
--------[B31] in ::--------
forall _i0 in [0,1,i),(= (select a _i0) 43);
 {exist _i0 in [0,1,100000),(= (select a _i0) 43)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 43)} || {exist _i0 in [0,1,100000),(= (select a _i0) 42)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 43)} || {forall _i0 in [0,1,100000),(= (select a _i0) 42)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43)} || {exist _i0 in [0,1,100000),(= (select a _i0) 42)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43)} || {forall _i0 in [0,1,100000),(= (select a _i0) 42)};
 
----------[B31]-> [B30] out -------:
(< i 100000);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 {exist _i0 in [0,1,100000),(= (select a _i0) 43)} || {(= i 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 43)} || {exist _i0 in [0,1,100000),(= (select a _i0) 42)};
 {exist _i0 in [0,1,100000),(= (select a _i0) 43)} || {forall _i0 in [0,1,100000),(= (select a _i0) 42)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43)} || {exist _i0 in [0,1,100000),(= (select a _i0) 42)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43)} || {forall _i0 in [0,1,100000),(= (select a _i0) 42)};
 
----------[B31]-> [B28] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 43);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 43);
 forall _i0 in [0,1,i),(= (select a _i0) 43);
 forall _i0 in [0,1,100000),(= (select a _i0) 43);
 
--------[B32] in ::--------
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 
----------[B32]-> [B31] out -------:
(= i 0);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 
--------[B33] in ::--------
exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 
----------[B33]-> [B35] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 
--------[B34] in ::--------
(< i 100000);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 {exist _i0 in [0,1,100000),(= (select a _i0) 42)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42)} || {(= i 0)};
 
----------[B34]-> [B33] out -------:
exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 
--------[B35] in ::--------
forall _i0 in [0,1,i),(= (select a _i0) 42);
 {exist _i0 in [0,1,100000),(= (select a _i0) 42)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42)} || {(= i 0)};
 
----------[B35]-> [B34] out -------:
(< i 100000);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 {exist _i0 in [0,1,100000),(= (select a _i0) 42)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42)} || {(= i 0)};
 
----------[B35]-> [B32] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) 42);
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) 42);
 forall _i0 in [0,1,i),(= (select a _i0) 42);
 forall _i0 in [0,1,100000),(= (select a _i0) 42);
 
--------[B36] in ::--------

----------[B36]-> [B35] out -------:
(= i 0);
 
--------[B37] in ::--------

----------[B37]-> [B36] out -------:

