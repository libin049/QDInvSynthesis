*******************process function::  main***************
--------[B0] in ::--------
(>= i 100000);
 (= _ret 0);
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,(- i 1)),(distinct (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,i),(distinct (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 forall _i0 in [0,1,(- i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 forall _i0 in [0,1,i),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 forall _i0 in [0,1,100000),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 {(distinct result 0)} || {(= result 0)};
 {(distinct result 0)} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {(= result 1)} || {(= result 0)};
 {(= result 1)} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {(>= x 100000)} || {(= result 0)};
 {(>= x 100000)} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {(= result 0)};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {forall _i0 in [0,1,(- i 1)),(= (select password _i0) (select guess _i0))} || {(= result 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select password _i0) (select guess _i0))} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))} || {(= result 0)};
 {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {(= result 0)};
 {forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {forall _i0 in [0,1,(- x 1)),(= (select password _i0) (select guess _i0))} || {(= result 0)};
 {forall _i0 in [0,1,(- x 1)),(= (select password _i0) (select guess _i0))} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {(= result 0)} || {forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))};
 
--------[B1] in ::--------
(>= i 100000);
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,(- i 1)),(distinct (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,i),(distinct (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 forall _i0 in [0,1,(- i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 forall _i0 in [0,1,i),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 forall _i0 in [0,1,100000),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 {(distinct result 0)} || {(= result 0)};
 {(distinct result 0)} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {(= result 1)} || {(= result 0)};
 {(= result 1)} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {(>= x 100000)} || {(= result 0)};
 {(>= x 100000)} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {(= result 0)};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {forall _i0 in [0,1,(- i 1)),(= (select password _i0) (select guess _i0))} || {(= result 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select password _i0) (select guess _i0))} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))} || {(= result 0)};
 {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {(= result 0)};
 {forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {forall _i0 in [0,1,(- x 1)),(= (select password _i0) (select guess _i0))} || {(= result 0)};
 {forall _i0 in [0,1,(- x 1)),(= (select password _i0) (select guess _i0))} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {(= result 0)} || {forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))};
 
----------[B1]-> [B0] out -------:
(>= i 100000);
 (= _ret 0);
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,(- i 1)),(distinct (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,i),(distinct (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 forall _i0 in [0,1,(- i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 forall _i0 in [0,1,i),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 forall _i0 in [0,1,100000),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 {(distinct result 0)} || {(= result 0)};
 {(distinct result 0)} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {(= result 1)} || {(= result 0)};
 {(= result 1)} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {(>= x 100000)} || {(= result 0)};
 {(>= x 100000)} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {(= result 0)};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {forall _i0 in [0,1,(- i 1)),(= (select password _i0) (select guess _i0))} || {(= result 0)};
 {forall _i0 in [0,1,(- i 1)),(= (select password _i0) (select guess _i0))} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))} || {(= result 0)};
 {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {(= result 0)};
 {forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {forall _i0 in [0,1,(- x 1)),(= (select password _i0) (select guess _i0))} || {(= result 0)};
 {forall _i0 in [0,1,(- x 1)),(= (select password _i0) (select guess _i0))} || {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 {(= result 0)} || {forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))};
 
--------[B2] in ::--------
(>= i 100000);
 (distinct result 0);
 (= result 1);
 (< x i);
 (< x 100000);
 exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,(- i 1)),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0));
 {forall _i0 in [0,1,(- x 1)),(= (select password _i0) (select guess _i0))} || {(= x 0)};
 forall _i0 in [0,1,x],(= (select password _i0) (select guess _i0));
 
----------[B2]-> [B3] out -------:
(>= i 100000);
 (distinct result 0);
 (= result 1);
 exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,(- i 1)),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,(- x 1)),(= (select password _i0) (select guess _i0));
 
--------[B3] in ::--------
(>= i 100000);
 (distinct result 0);
 (= result 1);
 exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,(- i 1)),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0));
 {forall _i0 in [0,1,(- x 1)),(= (select password _i0) (select guess _i0))} || {(= x 0)};
 
----------[B3]-> [B2] out -------:
(>= i 100000);
 (distinct result 0);
 (= result 1);
 (< x i);
 (< x 100000);
 exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,(- i 1)),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0));
 {forall _i0 in [0,1,(- x 1)),(= (select password _i0) (select guess _i0))} || {(= x 0)};
 forall _i0 in [0,1,x],(= (select password _i0) (select guess _i0));
 
----------[B3]-> [B1] out -------:
(>= i 100000);
 (distinct result 0);
 (= result 1);
 (>= x 100000);
 exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,(- i 1)),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,(- x 1)),(= (select password _i0) (select guess _i0));
 
--------[B4] in ::--------
(>= i 100000);
 (distinct result 0);
 (= result 1);
 exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,(- i 1)),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0));
 
----------[B4]-> [B3] out -------:
(>= i 100000);
 (distinct result 0);
 (= result 1);
 (= x 0);
 exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,(- i 1)),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0));
 
--------[B5] in ::--------
(>= i 100000);
 {(= result 0)} || {(= result 1)};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {(= result 1)};
 {(= result 0)} || {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))};
 {(= result 0)} || {forall _i0 in [0,1,(- i 1)),(= (select password _i0) (select guess _i0))};
 {(= result 0)} || {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,(- i 1)),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,(- i 1)),(distinct (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,i),(distinct (select password _i0) (select guess _i0))};
 forall _i0 in [0,1,(- i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 forall _i0 in [0,1,i),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 {(= result 0)} || {forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 forall _i0 in [0,1,100000),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 
----------[B5]-> [B4] out -------:
(>= i 100000);
 (distinct result 0);
 (= result 1);
 exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,(- i 1)),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0));
 
----------[B5]-> [B1] out -------:
(>= i 100000);
 (= result 0);
 exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0));
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,(- i 1)),(distinct (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,i),(distinct (select password _i0) (select guess _i0))};
 forall _i0 in [0,1,(- i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 forall _i0 in [0,1,i),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 forall _i0 in [0,1,100000),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 
--------[B6] in ::--------
(< i 100000);
 {(= result 0)} || {(= result 1)};
 {(= result 0)} || {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))};
 {(= result 0)} || {forall _i0 in [0,1,(+ i 1)),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {(= result 1)};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,(+ i 1)),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,i),(distinct (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,(+ i 1)),(distinct (select password _i0) (select guess _i0))};
 {(distinct (select password i) (select guess i))} || {(= (select password i) (select guess i))};
 {(distinct (select password i) (select guess i))} || {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))};
 {(= result 0)} || {(= (select password i) (select guess i))};
 {(= result 0)} || {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {(= (select password i) (select guess i))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))};
 forall _i0 in [0,1,i),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))}} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 
----------[B6]-> [B9] out -------:
{(= result 0)} || {(= result 1)};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {(= result 1)};
 {(= result 0)} || {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))};
 {(= result 0)} || {forall _i0 in [0,1,(- i 1)),(= (select password _i0) (select guess _i0))};
 {(= result 0)} || {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,(- i 1)),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,(- i 1)),(distinct (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,i),(distinct (select password _i0) (select guess _i0))};
 forall _i0 in [0,1,(- i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 forall _i0 in [0,1,i),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 
--------[B7] in ::--------
(< i 100000);
 (distinct (select password i) (select guess i));
 forall _i0 in [0,1,i),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 {(= result 0)} || {(= result 1)};
 {(= result 0)} || {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,i),(distinct (select password _i0) (select guess _i0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))}} || {(= result 1)};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))}} || {(= i 0)};
 exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0));
 forall _i0 in [0,1,(+ i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,(+ i 1)),(distinct (select password _i0) (select guess _i0))};
 
----------[B7]-> [B6] out -------:
(< i 100000);
 (distinct (select password i) (select guess i));
 (= result 0);
 exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0));
 forall _i0 in [0,1,i),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,i),(distinct (select password _i0) (select guess _i0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))}} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,(+ i 1)),(distinct (select password _i0) (select guess _i0))};
 
--------[B8] in ::--------
(< i 100000);
 forall _i0 in [0,1,i),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 {(= result 0)} || {(= result 1)};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {(= result 1)};
 {(= result 0)} || {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,i),(distinct (select password _i0) (select guess _i0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))}} || {(= result 1)};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))}} || {(= i 0)};
 
----------[B8]-> [B7] out -------:
(< i 100000);
 (distinct (select password i) (select guess i));
 forall _i0 in [0,1,i),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 {(= result 0)} || {(= result 1)};
 {(= result 0)} || {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,i),(distinct (select password _i0) (select guess _i0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))}} || {(= result 1)};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))}} || {(= i 0)};
 exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0));
 forall _i0 in [0,1,(+ i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,(+ i 1)),(distinct (select password _i0) (select guess _i0))};
 
----------[B8]-> [B6] out -------:
(< i 100000);
 (= (select password i) (select guess i));
 forall _i0 in [0,1,i),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 {(= result 0)} || {(= result 1)};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {(= result 1)};
 {(= result 0)} || {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))}} || {(= result 1)};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))}} || {(= i 0)};
 exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0));
 forall _i0 in [0,1,(+ i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 {(= result 0)} || {forall _i0 in [0,1,(+ i 1)),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,(+ i 1)),(= (select password _i0) (select guess _i0))};
 
--------[B9] in ::--------
forall _i0 in [0,1,i),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 {(= result 0)} || {(= result 1)};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {(= result 1)};
 {(= result 0)} || {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,i),(distinct (select password _i0) (select guess _i0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))}} || {(= result 1)};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))}} || {(= i 0)};
 
----------[B9]-> [B8] out -------:
(< i 100000);
 forall _i0 in [0,1,i),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 {(= result 0)} || {(= result 1)};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {(= result 1)};
 {(= result 0)} || {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,i),(distinct (select password _i0) (select guess _i0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))}} || {(= result 1)};
 {forall _i0 in [0,1,(- i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))}} || {(= i 0)};
 
----------[B9]-> [B5] out -------:
(>= i 100000);
 {(= result 0)} || {(= result 1)};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {(= result 1)};
 {(= result 0)} || {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))};
 {(= result 0)} || {forall _i0 in [0,1,(- i 1)),(= (select password _i0) (select guess _i0))};
 {(= result 0)} || {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,(- i 1)),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,i),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,(- i 1)),(distinct (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,i),(distinct (select password _i0) (select guess _i0))};
 forall _i0 in [0,1,(- i 1)),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 forall _i0 in [0,1,i),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 {(= result 0)} || {forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))};
 {exist _i0 in [0,1,100000),(= (select password _i0) (select guess _i0))} || {forall _i0 in [0,1,100000),(distinct (select password _i0) (select guess _i0))};
 forall _i0 in [0,1,100000),{(distinct (select password _i0) (select guess _i0))} || {(= (select password _i0) (select guess _i0))};
 
--------[B10] in ::--------

----------[B10]-> [B9] out -------:
(= result 1);
 (= i 0);
 
--------[B11] in ::--------

----------[B11]-> [B10] out -------:

