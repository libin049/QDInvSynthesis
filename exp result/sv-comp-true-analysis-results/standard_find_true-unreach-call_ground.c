*******************process function::  main***************
--------[B0] in ::--------
(>= x i);
 (= _ret 0);
 forall _i0 in [0,1,i),(distinct (select a _i0) e);
 {exist _i0 in [0,1,100000),(distinct (select a _i0) e)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)} || {(= i 0)};
 {(< i 100000)} || {(>= i 100000)};
 {(< i 100000)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(< i 100000)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {(< i 100000)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {(>= i 100000)};
 {(= (select a i) e)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {(>= i 100000)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {(>= i 100000)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {(>= i 100000)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,(- x 1)),(distinct (select a _i0) e)} || {(= x 0)};
 
--------[B1] in ::--------
(>= x i);
 forall _i0 in [0,1,i),(distinct (select a _i0) e);
 {exist _i0 in [0,1,100000),(distinct (select a _i0) e)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)} || {(= i 0)};
 {(< i 100000)} || {(>= i 100000)};
 {(< i 100000)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(< i 100000)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {(< i 100000)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {(>= i 100000)};
 {(= (select a i) e)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {(>= i 100000)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {(>= i 100000)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {(>= i 100000)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,(- x 1)),(distinct (select a _i0) e)} || {(= x 0)};
 
----------[B1]-> [B0] out -------:
(>= x i);
 (= _ret 0);
 forall _i0 in [0,1,i),(distinct (select a _i0) e);
 {exist _i0 in [0,1,100000),(distinct (select a _i0) e)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)} || {(= i 0)};
 {(< i 100000)} || {(>= i 100000)};
 {(< i 100000)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(< i 100000)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {(< i 100000)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {(>= i 100000)};
 {(= (select a i) e)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {(>= i 100000)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {(>= i 100000)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {(>= i 100000)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,(- x 1)),(distinct (select a _i0) e)} || {(= x 0)};
 
--------[B2] in ::--------
(< x i);
 forall _i0 in [0,1,i),(distinct (select a _i0) e);
 {exist _i0 in [0,1,100000),(distinct (select a _i0) e)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)} || {(= i 0)};
 {(< i 100000)} || {(>= i 100000)};
 {(< i 100000)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(< i 100000)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {(< i 100000)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {(>= i 100000)};
 {(= (select a i) e)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {(>= i 100000)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {(>= i 100000)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {(>= i 100000)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,(- x 1)),(distinct (select a _i0) e)} || {(= x 0)};
 forall _i0 in [0,1,x],(distinct (select a _i0) e);
 {(>= i 100000)} || {forall _i0 in [0,1,x],(distinct (select a _i0) (select a i))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) e)} || {forall _i0 in [0,1,x],(distinct (select a _i0) (select a i))};
 
----------[B2]-> [B3] out -------:
forall _i0 in [0,1,i),(distinct (select a _i0) e);
 {exist _i0 in [0,1,100000),(distinct (select a _i0) e)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)} || {(= i 0)};
 {(< i 100000)} || {(>= i 100000)};
 {(< i 100000)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(< i 100000)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {(< i 100000)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {(>= i 100000)};
 {(= (select a i) e)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {(>= i 100000)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {(>= i 100000)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {(>= i 100000)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 forall _i0 in [0,1,(- x 1)),(distinct (select a _i0) e);
 {(>= i 100000)} || {forall _i0 in [0,1,(- x 1)),(distinct (select a _i0) (select a i))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) e)} || {forall _i0 in [0,1,(- x 1)),(distinct (select a _i0) (select a i))};
 
--------[B3] in ::--------
forall _i0 in [0,1,i),(distinct (select a _i0) e);
 {exist _i0 in [0,1,100000),(distinct (select a _i0) e)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)} || {(= i 0)};
 {(< i 100000)} || {(>= i 100000)};
 {(< i 100000)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(< i 100000)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {(< i 100000)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {(>= i 100000)};
 {(= (select a i) e)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {(>= i 100000)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {(>= i 100000)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {(>= i 100000)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,(- x 1)),(distinct (select a _i0) e)} || {(= x 0)};
 
----------[B3]-> [B2] out -------:
(< x i);
 forall _i0 in [0,1,i),(distinct (select a _i0) e);
 {exist _i0 in [0,1,100000),(distinct (select a _i0) e)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)} || {(= i 0)};
 {(< i 100000)} || {(>= i 100000)};
 {(< i 100000)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(< i 100000)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {(< i 100000)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {(>= i 100000)};
 {(= (select a i) e)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {(>= i 100000)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {(>= i 100000)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {(>= i 100000)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,(- x 1)),(distinct (select a _i0) e)} || {(= x 0)};
 forall _i0 in [0,1,x],(distinct (select a _i0) e);
 {(>= i 100000)} || {forall _i0 in [0,1,x],(distinct (select a _i0) (select a i))};
 {exist _i0 in [0,1,100000),(distinct (select a _i0) e)} || {forall _i0 in [0,1,x],(distinct (select a _i0) (select a i))};
 
----------[B3]-> [B1] out -------:
(>= x i);
 forall _i0 in [0,1,i),(distinct (select a _i0) e);
 {exist _i0 in [0,1,100000),(distinct (select a _i0) e)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)} || {(= i 0)};
 {(< i 100000)} || {(>= i 100000)};
 {(< i 100000)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(< i 100000)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {(< i 100000)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {(>= i 100000)};
 {(= (select a i) e)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {(>= i 100000)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {(>= i 100000)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {(>= i 100000)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,(- x 1)),(distinct (select a _i0) e)} || {(= x 0)};
 
--------[B4] in ::--------
forall _i0 in [0,1,i),(distinct (select a _i0) e);
 {exist _i0 in [0,1,100000),(distinct (select a _i0) e)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)} || {(= i 0)};
 {(< i 100000)} || {(>= i 100000)};
 {(< i 100000)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(< i 100000)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {(< i 100000)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {(>= i 100000)};
 {(= (select a i) e)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {(>= i 100000)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {(>= i 100000)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {(>= i 100000)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 
----------[B4]-> [B3] out -------:
(= x 0);
 forall _i0 in [0,1,i),(distinct (select a _i0) e);
 {exist _i0 in [0,1,100000),(distinct (select a _i0) e)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)} || {(= i 0)};
 {(< i 100000)} || {(>= i 100000)};
 {(< i 100000)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(< i 100000)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {(< i 100000)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {(>= i 100000)};
 {(= (select a i) e)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {(= (select a i) e)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {(>= i 100000)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {forall _i0 in [0,1,i),(distinct (select a _i0) (select a i))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {(>= i 100000)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {exist _i0 in [0,1,100000),(= (select a _i0) e)} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {(>= i 100000)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {exist _i0 in [0,1,100000),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)};
 {exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1))} || {forall _i0 in [0,1,100000),(distinct (select a _i0) e)};
 
--------[B5] in ::--------
exist _i0 in [0,1,100000),(distinct (select a _i0) e);
 forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e);
 forall _i0 in [0,1,i),(distinct (select a _i0) e);
 
----------[B5]-> [B8] out -------:
exist _i0 in [0,1,100000),(distinct (select a _i0) e);
 forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e);
 forall _i0 in [0,1,i),(distinct (select a _i0) e);
 
--------[B6] in ::--------
(< i 100000);
 (distinct (select a i) e);
 forall _i0 in [0,1,i),(distinct (select a _i0) e);
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)} || {(= i 0)};
 exist _i0 in [0,1,100000),(distinct (select a _i0) e);
 forall _i0 in [0,1,(+ i 1)),(distinct (select a _i0) e);
 
----------[B6]-> [B5] out -------:
exist _i0 in [0,1,100000),(distinct (select a _i0) e);
 forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e);
 forall _i0 in [0,1,i),(distinct (select a _i0) e);
 
--------[B7] in ::--------
(< i 100000);
 forall _i0 in [0,1,i),(distinct (select a _i0) e);
 {exist _i0 in [0,1,100000),(distinct (select a _i0) e)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)} || {(= i 0)};
 
----------[B7]-> [B6] out -------:
(< i 100000);
 (distinct (select a i) e);
 forall _i0 in [0,1,i),(distinct (select a _i0) e);
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)} || {(= i 0)};
 exist _i0 in [0,1,100000),(distinct (select a _i0) e);
 forall _i0 in [0,1,(+ i 1)),(distinct (select a _i0) e);
 
----------[B7]-> [B4] out -------:
(< i 100000);
 (= (select a i) e);
 forall _i0 in [0,1,i),(distinct (select a _i0) e);
 {exist _i0 in [0,1,100000),(distinct (select a _i0) e)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)} || {(= i 0)};
 forall _i0 in [0,1,i),(distinct (select a _i0) (select a i));
 exist _i0 in [0,1,100000),(= (select a _i0) e);
 exist _i1 in [0,1,100000),forall _i0 in [0,1,_i1),(distinct (select a _i0) (select a _i1));
 
--------[B8] in ::--------
forall _i0 in [0,1,i),(distinct (select a _i0) e);
 {exist _i0 in [0,1,100000),(distinct (select a _i0) e)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)} || {(= i 0)};
 
----------[B8]-> [B7] out -------:
(< i 100000);
 forall _i0 in [0,1,i),(distinct (select a _i0) e);
 {exist _i0 in [0,1,100000),(distinct (select a _i0) e)} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e)} || {(= i 0)};
 
----------[B8]-> [B4] out -------:
(>= i 100000);
 exist _i0 in [0,1,100000),(distinct (select a _i0) e);
 forall _i0 in [0,1,(- i 1)),(distinct (select a _i0) e);
 forall _i0 in [0,1,i),(distinct (select a _i0) e);
 forall _i0 in [0,1,100000),(distinct (select a _i0) e);
 
--------[B9] in ::--------

----------[B9]-> [B8] out -------:
(= i 0);
 
--------[B10] in ::--------

----------[B10]-> [B9] out -------:

