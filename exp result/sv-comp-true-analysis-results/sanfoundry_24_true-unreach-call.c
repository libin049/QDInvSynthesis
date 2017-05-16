*******************process function::  printEven***************
--------[B0] in ::--------

--------[B1] in ::--------

----------[B1]-> [B0] out -------:

*******************process function::  printOdd***************
--------[B0] in ::--------

--------[B1] in ::--------

----------[B1]-> [B0] out -------:

*******************process function::  main***************
--------[B0] in ::--------
(>= i num);
 (= _ret 0);
 forall _i0 in [0,1,i),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(distinct (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))};
 forall _i0 in [0,1,num),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}} || {(= i 0)};
 forall _i0 in [0,1,num),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)};
 
--------[B1] in ::--------
(>= i num);
 forall _i0 in [0,1,i),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(distinct (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))};
 forall _i0 in [0,1,num),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}} || {(= i 0)};
 forall _i0 in [0,1,num),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)};
 
----------[B1]-> [B0] out -------:
(>= i num);
 (= _ret 0);
 forall _i0 in [0,1,i),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(distinct (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))};
 forall _i0 in [0,1,num),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}} || {(= i 0)};
 forall _i0 in [0,1,num),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)};
 
--------[B2] in ::--------
(< i num);
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i],(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,(+ i 1)),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,(+ i 1)),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,(+ i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,(+ i 1)],(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(distinct (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i],(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,(+ i 1)),(distinct (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,(+ i 1)],(distinct (mod (select array _i0) 2) 0)};
 {(distinct (mod (select array i) 2) 0)} || {(= (mod (select array i) 2) 0)};
 {(distinct (mod (select array i) 2) 0)} || {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 {(distinct (mod (select array i) 2) 0)} || {forall _i0 in [0,1,(+ i 1)],{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}};
 forall _i0 in [0,1,i),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 forall _i0 in [0,1,num),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}} || {(= i 0)};
 forall _i0 in [0,1,i],{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array i) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,(+ i 1)],{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}};
 forall _i0 in [0,1,(+ i 1)),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,(+ i 1)],{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)}};
 
----------[B2]-> [B5] out -------:
{exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))};
 forall _i0 in [0,1,num),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,(- i 1)),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,(- i 1)),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,(- i 1)),(distinct (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,(- i 1)),(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(distinct (mod (select array _i0) 2) 0)};
 forall _i0 in [0,1,(- i 1)),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 forall _i0 in [0,1,i),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 
--------[B3] in ::--------
(< i num);
 (distinct (mod (select array i) 2) 0);
 forall _i0 in [0,1,i),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(distinct (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))};
 forall _i0 in [0,1,num),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}} || {(= i 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i],(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i],(not (= (mod (select array _i0) 2) 0))};
 forall _i0 in [0,1,i],{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0);
 forall _i0 in [0,1,(+ i 1)),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,(+ i 1)),(distinct (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,(+ i 1)],(distinct (mod (select array _i0) 2) 0)};
 
----------[B3]-> [B2] out -------:
(< i num);
 (distinct (mod (select array i) 2) 0);
 forall _i0 in [0,1,i),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(distinct (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))};
 forall _i0 in [0,1,num),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}} || {(= i 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i],(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i],(not (= (mod (select array _i0) 2) 0))};
 forall _i0 in [0,1,i],{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0);
 forall _i0 in [0,1,(+ i 1)),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,(+ i 1)),(distinct (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,(+ i 1)],(distinct (mod (select array _i0) 2) 0)};
 
--------[B4] in ::--------
(< i num);
 forall _i0 in [0,1,i),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(distinct (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))};
 forall _i0 in [0,1,num),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}} || {(= i 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i],(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i],(not (= (mod (select array _i0) 2) 0))};
 forall _i0 in [0,1,i],{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 
----------[B4]-> [B3] out -------:
(< i num);
 (distinct (mod (select array i) 2) 0);
 forall _i0 in [0,1,i),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(distinct (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))};
 forall _i0 in [0,1,num),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}} || {(= i 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i],(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i],(not (= (mod (select array _i0) 2) 0))};
 forall _i0 in [0,1,i],{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0);
 forall _i0 in [0,1,(+ i 1)),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,(+ i 1)),(distinct (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,(+ i 1)],(distinct (mod (select array _i0) 2) 0)};
 
----------[B4]-> [B2] out -------:
(< i num);
 (= (mod (select array i) 2) 0);
 forall _i0 in [0,1,i),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 forall _i0 in [0,1,num),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}} || {(= i 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i],(= (mod (select array _i0) 2) 0)};
 forall _i0 in [0,1,i],{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0);
 forall _i0 in [0,1,(+ i 1)),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,(+ i 1)),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,(+ i 1)),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,(+ i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,(+ i 1)],(= (mod (select array _i0) 2) 0)};
 forall _i0 in [0,1,(+ i 1)],{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 
--------[B5] in ::--------
forall _i0 in [0,1,i),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(distinct (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))};
 forall _i0 in [0,1,num),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}} || {(= i 0)};
 
----------[B5]-> [B4] out -------:
(< i num);
 forall _i0 in [0,1,i),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(distinct (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))};
 forall _i0 in [0,1,num),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}} || {(= i 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i],(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i],(not (= (mod (select array _i0) 2) 0))};
 forall _i0 in [0,1,i],{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 
----------[B5]-> [B1] out -------:
(>= i num);
 forall _i0 in [0,1,i),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(distinct (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))};
 forall _i0 in [0,1,num),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {forall _i0 in [0,1,(- i 1)),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)}} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}} || {(= i 0)};
 forall _i0 in [0,1,num),{(distinct (mod (select array _i0) 2) 0)} || {(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(distinct (mod (select array _i0) 2) 0)};
 
--------[B6] in ::--------
(>= i num);
 forall _i0 in [0,1,i),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}} || {(= i 0)};
 forall _i0 in [0,1,num),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 
----------[B6]-> [B5] out -------:
(= i 0);
 forall _i0 in [0,1,num),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 
--------[B7] in ::--------
(< i num);
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,(+ i 1)),(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,(+ i 1)),(= (mod (select array _i0) 2) 0)};
 {(= (mod (select array i) 2) 0)} || {(not (= (mod (select array i) 2) 0))};
 {(= (mod (select array i) 2) 0)} || {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))};
 forall _i0 in [0,1,i),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}} || {(= i 0)};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array i) 2) 0))};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))};
 forall _i0 in [0,1,(+ i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 
----------[B7]-> [B10] out -------:
{exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,(- i 1)),(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,(- i 1)),(= (mod (select array _i0) 2) 0)};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 forall _i0 in [0,1,i),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 
--------[B8] in ::--------
(< i num);
 (= (mod (select array i) 2) 0);
 forall _i0 in [0,1,i),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}} || {(= i 0)};
 exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0);
 forall _i0 in [0,1,(+ i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,(+ i 1)),(= (mod (select array _i0) 2) 0)};
 
----------[B8]-> [B7] out -------:
(< i num);
 (= (mod (select array i) 2) 0);
 forall _i0 in [0,1,i),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}} || {(= i 0)};
 exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0);
 forall _i0 in [0,1,(+ i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,(+ i 1)),(= (mod (select array _i0) 2) 0)};
 
--------[B9] in ::--------
(< i num);
 forall _i0 in [0,1,i),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}} || {(= i 0)};
 
----------[B9]-> [B8] out -------:
(< i num);
 (= (mod (select array i) 2) 0);
 forall _i0 in [0,1,i),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}} || {(= i 0)};
 exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0);
 forall _i0 in [0,1,(+ i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,(+ i 1)),(= (mod (select array _i0) 2) 0)};
 
----------[B9]-> [B7] out -------:
(< i num);
 (not (= (mod (select array i) 2) 0));
 forall _i0 in [0,1,i),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(not (= (mod (select array _i0) 2) 0))};
 {forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}} || {(= i 0)};
 exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0));
 forall _i0 in [0,1,(+ i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,(+ i 1)),(not (= (mod (select array _i0) 2) 0))};
 
--------[B10] in ::--------
forall _i0 in [0,1,i),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}} || {(= i 0)};
 
----------[B10]-> [B9] out -------:
(< i num);
 forall _i0 in [0,1,i),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}} || {(= i 0)};
 
----------[B10]-> [B6] out -------:
(>= i num);
 forall _i0 in [0,1,i),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,i),(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,i),(= (mod (select array _i0) 2) 0)};
 {forall _i0 in [0,1,(- i 1)),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))}} || {(= i 0)};
 forall _i0 in [0,1,num),{(= (mod (select array _i0) 2) 0)} || {(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)} || {forall _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))};
 {exist _i0 in [0,1,num),(not (= (mod (select array _i0) 2) 0))} || {forall _i0 in [0,1,num),(= (mod (select array _i0) 2) 0)};
 
--------[B11] in ::--------

----------[B11]-> [B10] out -------:
(= i 0);
 
--------[B12] in ::--------

----------[B12]-> [B11] out -------:

