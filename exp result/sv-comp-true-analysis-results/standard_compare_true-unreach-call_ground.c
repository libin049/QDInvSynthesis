*******************process function::  main***************
--------[B0] in ::--------
(>= i 100000);
 (= _ret 0);
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(distinct (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 forall _i0 in [0,1,i),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 forall _i0 in [0,1,100000),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 {(distinct rv 0)} || {(= rv 0)};
 {(distinct rv 0)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {(= rv 1)} || {(= rv 0)};
 {(= rv 1)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {(>= x 100000)} || {(= rv 0)};
 {(>= x 100000)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {(= rv 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0))} || {(= rv 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))} || {(= rv 0)};
 {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {(= rv 0)};
 {forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {forall _i0 in [0,1,(- x 1)),(= (select a _i0) (select b _i0))} || {(= rv 0)};
 {forall _i0 in [0,1,(- x 1)),(= (select a _i0) (select b _i0))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {(= rv 0)} || {forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 
--------[B1] in ::--------
(>= i 100000);
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(distinct (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 forall _i0 in [0,1,i),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 forall _i0 in [0,1,100000),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 {(distinct rv 0)} || {(= rv 0)};
 {(distinct rv 0)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {(= rv 1)} || {(= rv 0)};
 {(= rv 1)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {(>= x 100000)} || {(= rv 0)};
 {(>= x 100000)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {(= rv 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0))} || {(= rv 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))} || {(= rv 0)};
 {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {(= rv 0)};
 {forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {forall _i0 in [0,1,(- x 1)),(= (select a _i0) (select b _i0))} || {(= rv 0)};
 {forall _i0 in [0,1,(- x 1)),(= (select a _i0) (select b _i0))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {(= rv 0)} || {forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 
----------[B1]-> [B0] out -------:
(>= i 100000);
 (= _ret 0);
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(distinct (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 forall _i0 in [0,1,i),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 forall _i0 in [0,1,100000),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 {(distinct rv 0)} || {(= rv 0)};
 {(distinct rv 0)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {(= rv 1)} || {(= rv 0)};
 {(= rv 1)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {(>= x 100000)} || {(= rv 0)};
 {(>= x 100000)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {(= rv 0)};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0))} || {(= rv 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))} || {(= rv 0)};
 {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {(= rv 0)};
 {forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {forall _i0 in [0,1,(- x 1)),(= (select a _i0) (select b _i0))} || {(= rv 0)};
 {forall _i0 in [0,1,(- x 1)),(= (select a _i0) (select b _i0))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 {(= rv 0)} || {forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 
--------[B2] in ::--------
(>= i 100000);
 (distinct rv 0);
 (= rv 1);
 (< x i);
 (< x 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,i),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0));
 {forall _i0 in [0,1,(- x 1)),(= (select a _i0) (select b _i0))} || {(= x 0)};
 forall _i0 in [0,1,x],(= (select a _i0) (select b _i0));
 
----------[B2]-> [B3] out -------:
(>= i 100000);
 (distinct rv 0);
 (= rv 1);
 exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,i),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,(- x 1)),(= (select a _i0) (select b _i0));
 
--------[B3] in ::--------
(>= i 100000);
 (distinct rv 0);
 (= rv 1);
 exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,i),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0));
 {forall _i0 in [0,1,(- x 1)),(= (select a _i0) (select b _i0))} || {(= x 0)};
 
----------[B3]-> [B2] out -------:
(>= i 100000);
 (distinct rv 0);
 (= rv 1);
 (< x i);
 (< x 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,i),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0));
 {forall _i0 in [0,1,(- x 1)),(= (select a _i0) (select b _i0))} || {(= x 0)};
 forall _i0 in [0,1,x],(= (select a _i0) (select b _i0));
 
----------[B3]-> [B1] out -------:
(>= i 100000);
 (distinct rv 0);
 (= rv 1);
 (>= x 100000);
 exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,i),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,(- x 1)),(= (select a _i0) (select b _i0));
 
--------[B4] in ::--------
(>= i 100000);
 (distinct rv 0);
 (= rv 1);
 exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,i),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0));
 
----------[B4]-> [B3] out -------:
(>= i 100000);
 (distinct rv 0);
 (= rv 1);
 (= x 0);
 exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,i),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0));
 
--------[B5] in ::--------
(>= i 100000);
 {(= rv 0)} || {(= rv 1)};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {(= rv 1)};
 {(= rv 0)} || {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 {(= rv 0)} || {forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0))};
 {(= rv 0)} || {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(distinct (select a _i0) (select b _i0))};
 forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 forall _i0 in [0,1,i),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 {(= rv 0)} || {forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 forall _i0 in [0,1,100000),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 
----------[B5]-> [B4] out -------:
(>= i 100000);
 (distinct rv 0);
 (= rv 1);
 exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,i),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0));
 
----------[B5]-> [B1] out -------:
(>= i 100000);
 (= rv 0);
 exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0));
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(distinct (select a _i0) (select b _i0))};
 forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 forall _i0 in [0,1,i),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 forall _i0 in [0,1,100000),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 
--------[B6] in ::--------
{(= rv 0)} || {(= rv 1)};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {(= rv 1)};
 {(= rv 0)} || {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 {(= rv 0)} || {forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0))};
 {(= rv 0)} || {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(distinct (select a _i0) (select b _i0))};
 forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 forall _i0 in [0,1,i),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 
----------[B6]-> [B10] out -------:
{(= rv 0)} || {(= rv 1)};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {(= rv 1)};
 {(= rv 0)} || {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 {(= rv 0)} || {forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0))};
 {(= rv 0)} || {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(distinct (select a _i0) (select b _i0))};
 forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 forall _i0 in [0,1,i),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 
--------[B7] in ::--------
(< i 100000);
 {(= rv 0)} || {(= rv 1)};
 {(= rv 0)} || {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))};
 {(= rv 0)} || {forall _i0 in [0,1,(+ i 1)),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {(= rv 1)};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {forall _i0 in [0,1,(+ i 1)),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(distinct (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,(+ i 1)),(distinct (select a _i0) (select b _i0))};
 {(distinct (select a i) (select b i))} || {(= (select a i) (select b i))};
 {(distinct (select a i) (select b i))} || {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 {(= rv 0)} || {(= (select a i) (select b i))};
 {(= rv 0)} || {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {(= (select a i) (select b i))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 forall _i0 in [0,1,i),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))}} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 
----------[B7]-> [B6] out -------:
{(= rv 0)} || {(= rv 1)};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {(= rv 1)};
 {(= rv 0)} || {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 {(= rv 0)} || {forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0))};
 {(= rv 0)} || {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(distinct (select a _i0) (select b _i0))};
 forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 forall _i0 in [0,1,i),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 
--------[B8] in ::--------
(< i 100000);
 (distinct (select a i) (select b i));
 forall _i0 in [0,1,i),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 {(= rv 0)} || {(= rv 1)};
 {(= rv 0)} || {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(distinct (select a _i0) (select b _i0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))}} || {(= rv 1)};
 exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0));
 forall _i0 in [0,1,(+ i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,(+ i 1)),(distinct (select a _i0) (select b _i0))};
 
----------[B8]-> [B7] out -------:
(< i 100000);
 (distinct (select a i) (select b i));
 (= rv 0);
 exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0));
 forall _i0 in [0,1,i),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(distinct (select a _i0) (select b _i0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))}} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,(+ i 1)),(distinct (select a _i0) (select b _i0))};
 
--------[B9] in ::--------
(< i 100000);
 forall _i0 in [0,1,i),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 {(= rv 0)} || {(= rv 1)};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {(= rv 1)};
 {(= rv 0)} || {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(distinct (select a _i0) (select b _i0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))}} || {(= rv 1)};
 
----------[B9]-> [B8] out -------:
(< i 100000);
 (distinct (select a i) (select b i));
 forall _i0 in [0,1,i),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 {(= rv 0)} || {(= rv 1)};
 {(= rv 0)} || {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(distinct (select a _i0) (select b _i0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))}} || {(= rv 1)};
 exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0));
 forall _i0 in [0,1,(+ i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,(+ i 1)),(distinct (select a _i0) (select b _i0))};
 
----------[B9]-> [B7] out -------:
(< i 100000);
 (= (select a i) (select b i));
 forall _i0 in [0,1,i),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 {(= rv 0)} || {(= rv 1)};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {(= rv 1)};
 {(= rv 0)} || {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))}} || {(= rv 1)};
 exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0));
 forall _i0 in [0,1,(+ i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 {(= rv 0)} || {forall _i0 in [0,1,(+ i 1)),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {forall _i0 in [0,1,(+ i 1)),(= (select a _i0) (select b _i0))};
 
--------[B10] in ::--------
forall _i0 in [0,1,i),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 {(= rv 0)} || {(= rv 1)};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {(= rv 1)};
 {(= rv 0)} || {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(distinct (select a _i0) (select b _i0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))}} || {(= rv 1)};
 
----------[B10]-> [B9] out -------:
(< i 100000);
 forall _i0 in [0,1,i),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 {(= rv 0)} || {(= rv 1)};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {(= rv 1)};
 {(= rv 0)} || {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(distinct (select a _i0) (select b _i0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))}} || {(= rv 1)};
 
----------[B10]-> [B5] out -------:
(>= i 100000);
 {(= rv 0)} || {(= rv 1)};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {(= rv 1)};
 {(= rv 0)} || {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 {(= rv 0)} || {forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0))};
 {(= rv 0)} || {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {forall _i0 in [0,1,(- i 1)),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,i),(distinct (select a _i0) (select b _i0))};
 forall _i0 in [0,1,(- i 1)),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 forall _i0 in [0,1,i),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 {(= rv 0)} || {forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))} || {forall _i0 in [0,1,100000),(= (select a _i0) (select b _i0))};
 {exist _i0 in [0,1,100000),(= (select a _i0) (select b _i0))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) (select b _i0))};
 forall _i0 in [0,1,100000),{(distinct (select a _i0) (select b _i0))} || {(= (select a _i0) (select b _i0))};
 
--------[B11] in ::--------

----------[B11]-> [B10] out -------:
(= i 0);
 (= rv 1);
 
--------[B12] in ::--------

----------[B12]-> [B11] out -------:

