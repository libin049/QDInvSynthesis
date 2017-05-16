*******************process function::  main***************
--------[B0] in ::--------
(>= i 100000);
 (>= x j);
 (= _ret 0);
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(- i 1)),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select B _i0))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,100000),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,100000),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- x 1)),(< (select C _i0) 100000)} || {(= x 0)};
 
--------[B1] in ::--------
(>= i 100000);
 (>= x j);
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(- i 1)),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select B _i0))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,100000),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,100000),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- x 1)),(< (select C _i0) 100000)} || {(= x 0)};
 
----------[B1]-> [B0] out -------:
(>= i 100000);
 (>= x j);
 (= _ret 0);
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(- i 1)),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select B _i0))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,100000),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,100000),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- x 1)),(< (select C _i0) 100000)} || {(= x 0)};
 
--------[B2] in ::--------
(>= i 100000);
 (< x j);
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(- i 1)),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select B _i0))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,100000),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,100000),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- x 1)),(< (select C _i0) 100000)} || {(= x 0)};
 forall _i0 in [0,1,x],(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,x],(= (select C _i0) 0)};
 
----------[B2]-> [B3] out -------:
(>= i 100000);
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(- i 1)),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select B _i0))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,100000),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,100000),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 forall _i0 in [0,1,(- x 1)),(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(- x 1)),(= (select C _i0) 0)};
 
--------[B3] in ::--------
(>= i 100000);
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(- i 1)),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select B _i0))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,100000),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,100000),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- x 1)),(< (select C _i0) 100000)} || {(= x 0)};
 
----------[B3]-> [B2] out -------:
(>= i 100000);
 (< x j);
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(- i 1)),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select B _i0))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,100000),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,100000),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- x 1)),(< (select C _i0) 100000)} || {(= x 0)};
 forall _i0 in [0,1,x],(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,x],(= (select C _i0) 0)};
 
----------[B3]-> [B1] out -------:
(>= i 100000);
 (>= x j);
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(- i 1)),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select B _i0))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,100000),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,100000),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- x 1)),(< (select C _i0) 100000)} || {(= x 0)};
 
--------[B4] in ::--------
(>= i 100000);
 (>= x j);
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(- i 1)),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select B _i0))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,100000),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,100000),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- x 1)),(< (select C _i0) 100000)} || {(= x 0)};
 
----------[B4]-> [B3] out -------:
(>= i 100000);
 (= x 0);
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(- i 1)),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select B _i0))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,100000),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,100000),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 
--------[B5] in ::--------
(>= i 100000);
 (< x j);
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(- i 1)),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select B _i0))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,100000),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,100000),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- x 1)),(< (select C _i0) 100000)} || {(= x 0)};
 forall _i0 in [0,1,x],(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,x],(= (select C _i0) 0)};
 
----------[B5]-> [B6] out -------:
(>= i 100000);
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(- i 1)),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select B _i0))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,100000),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,100000),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 forall _i0 in [0,1,(- x 1)),(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(- x 1)),(= (select C _i0) 0)};
 
--------[B6] in ::--------
(>= i 100000);
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(- i 1)),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select B _i0))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,100000),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,100000),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- x 1)),(< (select C _i0) 100000)} || {(= x 0)};
 
----------[B6]-> [B5] out -------:
(>= i 100000);
 (< x j);
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(- i 1)),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select B _i0))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,100000),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,100000),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- x 1)),(< (select C _i0) 100000)} || {(= x 0)};
 forall _i0 in [0,1,x],(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,x],(= (select C _i0) 0)};
 
----------[B6]-> [B4] out -------:
(>= i 100000);
 (>= x j);
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(- i 1)),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select B _i0))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,100000),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,100000),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- x 1)),(< (select C _i0) 100000)} || {(= x 0)};
 
--------[B7] in ::--------
(>= i 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(- i 1)),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select B _i0))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,100000),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,100000),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 
----------[B7]-> [B6] out -------:
(>= i 100000);
 (= x 0);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(- i 1)),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select B _i0))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,100000),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,100000),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 
--------[B8] in ::--------
(< i 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(+ i 1)),(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(+ i 1)),(= (select A _i0) (select B _i0))};
 {(= (select A i) (select B i))} || {(not (= (select A i) (select B i)))};
 {(= (select A i) (select B i))} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(not (= (select A i) (select B i)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))}} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {(not (= (select A i) (select B i)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 
----------[B8]-> [B11] out -------:
{exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(- i 1)),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select B _i0))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 
--------[B9] in ::--------
(< i 100000);
 (= (select A i) (select B i));
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 {forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))}} || {(= j 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))}} || {(= i 0)};
 exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0));
 forall _i0 in [0,1,(+ i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(+ i 1)),(= (select A _i0) (select B _i0))};
 
----------[B9]-> [B8] out -------:
(< i 100000);
 (= (select A i) (select B i));
 exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0));
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 {forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))}} || {(= i 0)};
 forall _i0 in [0,1,(+ i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(+ i 1)),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000);
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 
--------[B10] in ::--------
(< i 100000);
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 {forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))}} || {(= j 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))}} || {(= i 0)};
 
----------[B10]-> [B9] out -------:
(< i 100000);
 (= (select A i) (select B i));
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 {forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))}} || {(= j 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))}} || {(= i 0)};
 exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0));
 forall _i0 in [0,1,(+ i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(+ i 1)),(= (select A _i0) (select B _i0))};
 
----------[B10]-> [B8] out -------:
(< i 100000);
 (not (= (select A i) (select B i)));
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))}} || {(= j 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))}} || {(= i 0)};
 exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)));
 forall _i0 in [0,1,(+ i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(+ i 1)),(not (= (select A _i0) (select B _i0)))};
 
--------[B11] in ::--------
forall _i0 in [0,1,j),(< (select C _i0) 100000);
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 {forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))}} || {(= j 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))}} || {(= i 0)};
 
----------[B11]-> [B10] out -------:
(< i 100000);
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 {forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))}} || {(= j 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))}} || {(= i 0)};
 
----------[B11]-> [B7] out -------:
(>= i 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {(= j 0)};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {forall _i0 in [0,1,j),(= (select C _i0) 0)};
 forall _i0 in [0,1,j),(< (select C _i0) 100000);
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {forall _i0 in [0,1,(- j 1)),(< (select C _i0) 100000)} || {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,(- i 1)),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,i),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,(- i 1)),(= (select A _i0) (select B _i0))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,i),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,(- i 1)),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 forall _i0 in [0,1,i),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(= (select A _i0) (select B _i0))} || {forall _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))};
 {exist _i0 in [0,1,100000),(not (= (select A _i0) (select B _i0)))} || {forall _i0 in [0,1,100000),(= (select A _i0) (select B _i0))};
 forall _i0 in [0,1,100000),{(= (select A _i0) (select B _i0))} || {(not (= (select A _i0) (select B _i0)))};
 
--------[B12] in ::--------

----------[B12]-> [B11] out -------:
(= j 0);
 (= i 0);
 
--------[B13] in ::--------

----------[B13]-> [B12] out -------:

