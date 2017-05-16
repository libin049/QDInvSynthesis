*******************process function::  main***************
--------[B0] in ::--------
(>= i 100000);
 (= _ret 0);
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(< (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,i),(< (select a _i0) 0)};
 forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,100000),(< (select a _i0) 0)};
 
--------[B1] in ::--------
(>= i 100000);
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(< (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,i),(< (select a _i0) 0)};
 forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,100000),(< (select a _i0) 0)};
 
----------[B1]-> [B0] out -------:
(>= i 100000);
 (= _ret 0);
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(< (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,i),(< (select a _i0) 0)};
 forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,100000),(< (select a _i0) 0)};
 
--------[B2] in ::--------
{exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(< (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,i),(< (select a _i0) 0)};
 forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 
----------[B2]-> [B10] out -------:
{exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(< (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,i),(< (select a _i0) 0)};
 forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 
--------[B3] in ::--------
(< i 100000);
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,i),(< (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(< (select a _i0) 0)};
 {(< (select a i) 0)} || {(>= (select a i) 0)};
 {(< (select a i) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {(>= (select a i) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 
----------[B3]-> [B2] out -------:
{exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(< (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,i),(< (select a _i0) 0)};
 forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 
--------[B4] in ::--------
(< i 100000);
 (< (select a i) 0);
 (distinct (select b i) 0);
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,i),(< (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= f 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 exist _i0 in [0,1,100000),(< (select a _i0) 0);
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(< (select a _i0) 0)};
 exist _i0 in [0,1,100000),(distinct (select b _i0) 0);
 
----------[B4]-> [B3] out -------:
(< i 100000);
 (< (select a i) 0);
 (distinct (select b i) 0);
 (= f 0);
 exist _i0 in [0,1,100000),(< (select a _i0) 0);
 exist _i0 in [0,1,100000),(distinct (select b _i0) 0);
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,i),(< (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(< (select a _i0) 0)};
 
--------[B5] in ::--------
(< i 100000);
 (< (select a i) 0);
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,i),(< (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= f 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 exist _i0 in [0,1,100000),(< (select a _i0) 0);
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(< (select a _i0) 0)};
 
----------[B5]-> [B4] out -------:
(< i 100000);
 (< (select a i) 0);
 (distinct (select b i) 0);
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,i),(< (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= f 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 exist _i0 in [0,1,100000),(< (select a _i0) 0);
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(< (select a _i0) 0)};
 exist _i0 in [0,1,100000),(distinct (select b _i0) 0);
 
----------[B5]-> [B3] out -------:
(< i 100000);
 (< (select a i) 0);
 (= (select b i) 0);
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,i),(< (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= f 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 exist _i0 in [0,1,100000),(< (select a _i0) 0);
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(< (select a _i0) 0)};
 exist _i0 in [0,1,100000),(= (select b _i0) 0);
 
--------[B6] in ::--------
(< i 100000);
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,i),(< (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(< (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {(>= (select a i) 0)} || {(< (select a i) 0)};
 {(>= (select a i) 0)} || {exist _i0 in [0,1,100000),(< (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {(< (select a i) 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {exist _i0 in [0,1,100000),(< (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),{(>= (select a _i0) 0)} || {(< (select a _i0) 0)}};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),{(>= (select a _i0) 0)} || {(< (select a _i0) 0)}};
 
----------[B6]-> [B5] out -------:
(< i 100000);
 (< (select a i) 0);
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,i),(< (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= f 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 exist _i0 in [0,1,100000),(< (select a _i0) 0);
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(< (select a _i0) 0)};
 
----------[B6]-> [B3] out -------:
(< i 100000);
 (>= (select a i) 0);
 {(= f 0)} || {(= f 1)};
 exist _i0 in [0,1,100000),(>= (select a _i0) 0);
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {(not (distinct (select b i) 0))} || {(distinct (select b i) 0)};
 {(not (distinct (select b i) 0))} || {exist _i0 in [0,1,100000),(distinct (select b _i0) 0)};
 {(= f 0)} || {(distinct (select b i) 0)};
 {(= f 0)} || {exist _i0 in [0,1,100000),(distinct (select b _i0) 0)};
 {exist _i0 in [0,1,100000),(not (distinct (select b _i0) 0))} || {(distinct (select b i) 0)};
 {exist _i0 in [0,1,100000),(not (distinct (select b _i0) 0))} || {exist _i0 in [0,1,100000),(distinct (select b _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 
--------[B7] in ::--------
(< i 100000);
 (>= (select a i) 0);
 (not (distinct (select b i) 0));
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= f 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 exist _i0 in [0,1,100000),(>= (select a _i0) 0);
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(>= (select a _i0) 0)};
 exist _i0 in [0,1,100000),(not (distinct (select b _i0) 0));
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 
----------[B7]-> [B6] out -------:
(< i 100000);
 (>= (select a i) 0);
 (not (distinct (select b i) 0));
 (= f 0);
 exist _i0 in [0,1,100000),(>= (select a _i0) 0);
 exist _i0 in [0,1,100000),(not (distinct (select b _i0) 0));
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 
--------[B8] in ::--------
(< i 100000);
 (>= (select a i) 0);
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= f 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 exist _i0 in [0,1,100000),(>= (select a _i0) 0);
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(>= (select a _i0) 0)};
 
----------[B8]-> [B7] out -------:
(< i 100000);
 (>= (select a i) 0);
 (not (distinct (select b i) 0));
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= f 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 exist _i0 in [0,1,100000),(>= (select a _i0) 0);
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(>= (select a _i0) 0)};
 exist _i0 in [0,1,100000),(not (distinct (select b _i0) 0));
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 
----------[B8]-> [B6] out -------:
(< i 100000);
 (>= (select a i) 0);
 (distinct (select b i) 0);
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= f 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 exist _i0 in [0,1,100000),(>= (select a _i0) 0);
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(>= (select a _i0) 0)};
 exist _i0 in [0,1,100000),(distinct (select b _i0) 0);
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 
--------[B9] in ::--------
(< i 100000);
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,i),(< (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= f 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 
----------[B9]-> [B8] out -------:
(< i 100000);
 (>= (select a i) 0);
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= f 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 exist _i0 in [0,1,100000),(>= (select a _i0) 0);
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(>= (select a _i0) 0)};
 
----------[B9]-> [B6] out -------:
(< i 100000);
 (< (select a i) 0);
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,i),(< (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= f 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 exist _i0 in [0,1,100000),(< (select a _i0) 0);
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(< (select a _i0) 0)};
 
--------[B10] in ::--------
forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,i),(< (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= f 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 
----------[B10]-> [B9] out -------:
(< i 100000);
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,i),(< (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= f 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 
----------[B10]-> [B1] out -------:
(>= i 100000);
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {(= f 0)} || {(= f 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(< (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,i),(< (select a _i0) 0)};
 forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),{(not (distinct (select b _i0) 0))} || {(distinct (select b _i0) 0)}};
 {exist _i0 in [0,1,100000),(>= (select a _i0) 0)} || {forall _i0 in [0,1,100000),(< (select a _i0) 0)};
 
--------[B11] in ::--------
(>= i 100000);
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(= (select b _i0) 1)};
 forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 
----------[B11]-> [B10] out -------:
(= f 1);
 (= i 0);
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 
--------[B12] in ::--------
{exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(= (select b _i0) 1)};
 forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 
----------[B12]-> [B17] out -------:
{exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(= (select b _i0) 1)};
 forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 
--------[B13] in ::--------
(< i 100000);
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(= (select b _i0) 1)};
 {(< (select a i) 0)} || {(>= (select a i) 0)};
 {(< (select a i) 0)} || {(= (select b i) 1)};
 {(< (select a i) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {(< (select a i) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {(= (select b i) 0)} || {(>= (select a i) 0)};
 {(= (select b i) 0)} || {(= (select b i) 1)};
 {(= (select b i) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {(= (select b i) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {(>= (select a i) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {(= (select b i) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {(>= (select a i) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {(= (select b i) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(= (select b _i0) 1)}} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 
----------[B13]-> [B12] out -------:
{exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(= (select b _i0) 1)};
 forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 
--------[B14] in ::--------
(< i 100000);
 (< (select a i) 0);
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(= (select b _i0) 1)}} || {(= i 0)};
 exist _i0 in [0,1,100000),(< (select a _i0) 0);
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 
----------[B14]-> [B13] out -------:
(< i 100000);
 (< (select a i) 0);
 (= (select b i) 0);
 exist _i0 in [0,1,100000),(< (select a _i0) 0);
 exist _i0 in [0,1,100000),(= (select b _i0) 0);
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(= (select b _i0) 1)}} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 
--------[B15] in ::--------
(< i 100000);
 (>= (select a i) 0);
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(= (select b _i0) 1)}} || {(= i 0)};
 exist _i0 in [0,1,100000),(>= (select a _i0) 0);
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(>= (select a _i0) 0)};
 
----------[B15]-> [B13] out -------:
(< i 100000);
 (>= (select a i) 0);
 (= (select b i) 1);
 exist _i0 in [0,1,100000),(>= (select a _i0) 0);
 exist _i0 in [0,1,100000),(= (select b _i0) 1);
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(= (select b _i0) 1)}} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(>= (select a _i0) 0)};
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(= (select b _i0) 1)};
 
--------[B16] in ::--------
(< i 100000);
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(= (select b _i0) 1)}} || {(= i 0)};
 
----------[B16]-> [B15] out -------:
(< i 100000);
 (>= (select a i) 0);
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(= (select b _i0) 1)}} || {(= i 0)};
 exist _i0 in [0,1,100000),(>= (select a _i0) 0);
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(+ i 1)),(>= (select a _i0) 0)};
 
----------[B16]-> [B14] out -------:
(< i 100000);
 (< (select a i) 0);
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(= (select b _i0) 1)}} || {(= i 0)};
 exist _i0 in [0,1,100000),(< (select a _i0) 0);
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,(+ i 1)),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 
--------[B17] in ::--------
forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(= (select b _i0) 1)}} || {(= i 0)};
 
----------[B17]-> [B16] out -------:
(< i 100000);
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(= (select b _i0) 1)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(= (select b _i0) 1)}} || {(= i 0)};
 
----------[B17]-> [B11] out -------:
(>= i 100000);
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select b _i0) 0)} || {exist _i0 in [0,1,100000),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,(- i 1)),(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,i),(= (select b _i0) 1)};
 forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,(- i 1)),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,i),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select a _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select a _i0) 0)} || {forall _i0 in [0,1,100000),(= (select b _i0) 1)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(>= (select a _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select a _i0) 0)} || {(= (select b _i0) 1)};
 
--------[B18] in ::--------

----------[B18]-> [B17] out -------:
(= i 0);
 
--------[B19] in ::--------

----------[B19]-> [B18] out -------:

