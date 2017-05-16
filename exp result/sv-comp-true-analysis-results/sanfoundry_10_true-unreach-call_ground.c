*******************process function::  main***************
--------[B0] in ::--------
(= n 100000);
 (= _ret 0);
 {(< pos n)} || {(not (distinct found 0))};
 {(< pos n)} || {(>= i n)};
 {(< pos n)} || {(= found 0)};
 {(< pos n)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {forall _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {(>= i n)};
 {(distinct found 0)} || {(= found 0)};
 {(distinct found 0)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {forall _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {(>= i n)};
 {(>= i (- n 1))} || {(= found 0)};
 {(>= i (- n 1))} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {forall _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(>= x pos)} || {(>= i n)};
 {(>= x pos)} || {(= found 0)};
 {(>= x pos)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(>= x pos)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(>= x pos)} || {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))};
 {(>= x pos)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {(>= x pos)} || {forall _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(>= x pos)} || {forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 
--------[B1] in ::--------
{(< pos n)} || {(not (distinct found 0))};
 (= n 100000);
 {(< pos n)} || {(>= i n)};
 {(< pos n)} || {(= found 0)};
 {(< pos n)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {forall _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {(>= i n)};
 {(distinct found 0)} || {(= found 0)};
 {(distinct found 0)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {forall _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {(>= i n)};
 {(>= i (- n 1))} || {(= found 0)};
 {(>= i (- n 1))} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {forall _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(>= x pos)} || {(>= i n)};
 {(>= x pos)} || {(= found 0)};
 {(>= x pos)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(>= x pos)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(>= x pos)} || {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))};
 {(>= x pos)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {(>= x pos)} || {forall _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(>= x pos)} || {forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 
----------[B1]-> [B0] out -------:
(= n 100000);
 (= _ret 0);
 {(< pos n)} || {(not (distinct found 0))};
 {(< pos n)} || {(>= i n)};
 {(< pos n)} || {(= found 0)};
 {(< pos n)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {forall _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {(>= i n)};
 {(distinct found 0)} || {(= found 0)};
 {(distinct found 0)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {forall _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {(>= i n)};
 {(>= i (- n 1))} || {(= found 0)};
 {(>= i (- n 1))} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {forall _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(>= x pos)} || {(>= i n)};
 {(>= x pos)} || {(= found 0)};
 {(>= x pos)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(>= x pos)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(>= x pos)} || {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))};
 {(>= x pos)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {(>= x pos)} || {forall _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(>= x pos)} || {forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 
--------[B2] in ::--------
(< pos n);
 (= n 100000);
 (distinct found 0);
 (>= i (- n 1));
 (< x n);
 (< x pos);
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(< i n)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(= i pos)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,n),(= (select vectorx _i0) element)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)};
 
----------[B2]-> [B3] out -------:
(< pos n);
 (= n 100000);
 (distinct found 0);
 (>= i (- n 1));
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(< i n)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(= i pos)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,n),(= (select vectorx _i0) element)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)};
 
--------[B3] in ::--------
(< pos n);
 (= n 100000);
 (distinct found 0);
 (>= i (- n 1));
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(< i n)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(= i pos)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,n),(= (select vectorx _i0) element)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)};
 
----------[B3]-> [B2] out -------:
(< pos n);
 (= n 100000);
 (distinct found 0);
 (>= i (- n 1));
 (< x n);
 (< x pos);
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(< i n)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(= i pos)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,n),(= (select vectorx _i0) element)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)};
 
----------[B3]-> [B1] out -------:
(< pos n);
 (= n 100000);
 (distinct found 0);
 (>= i (- n 1));
 (>= x pos);
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(< i n)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(= i pos)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,n),(= (select vectorx _i0) element)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)};
 
--------[B4] in ::--------
(< pos n);
 (= n 100000);
 (distinct found 0);
 (>= i (- n 1));
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(< i n)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(= i pos)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,n),(= (select vectorx _i0) element)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)};
 
----------[B4]-> [B3] out -------:
(< pos n);
 (= n 100000);
 (distinct found 0);
 (>= i (- n 1));
 (= x 0);
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(< i n)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(= i pos)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,n),(= (select vectorx _i0) element)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)};
 
--------[B5] in ::--------
{(< pos n)} || {(not (distinct found 0))};
 (= n 100000);
 {(< pos n)} || {(>= i n)};
 {(< pos n)} || {(= found 0)};
 {(< pos n)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {forall _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {(>= i n)};
 {(distinct found 0)} || {(= found 0)};
 {(distinct found 0)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {forall _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(distinct found 0)} || {forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {(>= i n)};
 {(>= i (- n 1))} || {(= found 0)};
 {(>= i (- n 1))} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {forall _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(>= i (- n 1))} || {forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 
----------[B5]-> [B4] out -------:
(< pos n);
 (= n 100000);
 (distinct found 0);
 (>= i (- n 1));
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(< i n)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(= i pos)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,n),(= (select vectorx _i0) element)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)};
 
----------[B5]-> [B1] out -------:
(= n 100000);
 (>= i n);
 (= found 0);
 {(< pos n)} || {(not (distinct found 0))};
 exist _i0 in [0,1,n),(not (= (select vectorx _i0) element));
 exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element));
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {(not (distinct found 0))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {(not (distinct found 0))};
 {forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element))} || {(not (distinct found 0))};
 forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element));
 forall _i0 in [0,1,i),(not (= (select vectorx _i0) element));
 forall _i0 in [0,1,n),(not (= (select vectorx _i0) element));
 forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element));
 
--------[B6] in ::--------
(< pos n);
 (= n 100000);
 (distinct found 0);
 (< i (- n 1));
 (= (select vectorx i) (select vectorx (+ i 1)));
 exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)));
 
----------[B6]-> [B8] out -------:
(< pos n);
 (= n 100000);
 (distinct found 0);
 exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)));
 
--------[B7] in ::--------
(< pos n);
 (= n 100000);
 (distinct found 0);
 (< i (- n 1));
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(< i n)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(= i pos)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,n),(= (select vectorx _i0) element)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)};
 
----------[B7]-> [B6] out -------:
(< pos n);
 (= n 100000);
 (distinct found 0);
 (< i (- n 1));
 (= (select vectorx i) (select vectorx (+ i 1)));
 exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)));
 
--------[B8] in ::--------
(< pos n);
 (= n 100000);
 (distinct found 0);
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(< i n)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(= i pos)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,n),(= (select vectorx _i0) element)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)};
 
----------[B8]-> [B7] out -------:
(< pos n);
 (= n 100000);
 (distinct found 0);
 (< i (- n 1));
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(< i n)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(= i pos)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,n),(= (select vectorx _i0) element)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)};
 
----------[B8]-> [B5] out -------:
(< pos n);
 (= n 100000);
 (distinct found 0);
 (>= i (- n 1));
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(< i n)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {(= i pos)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,n),(= (select vectorx _i0) element)};
 {exist _i0 in [pos,1,(- n 1)),(= (select vectorx _i0) (select vectorx (+ _i0 1)))} || {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)};
 
--------[B9] in ::--------
(= n 100000);
 (distinct found 0);
 (< pos n);
 exist _i0 in [0,1,n),(= (select vectorx _i0) element);
 exist _i0 in [0,1,100000),(= (select vectorx _i0) element);
 forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element));
 {(< i n)} || {(>= i n)};
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {(= found 1)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 
----------[B9]-> [B8] out -------:
(< i n);
 (< pos n);
 (= n 100000);
 (distinct found 0);
 (= i pos);
 exist _i0 in [0,1,n),(= (select vectorx _i0) element);
 exist _i0 in [0,1,100000),(= (select vectorx _i0) element);
 
--------[B10] in ::--------
(= n 100000);
 {(< pos n)} || {(= found 0)};
 {(< pos n)} || {(not (distinct found 0))};
 {(< pos n)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {forall _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {(= found 0)};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {(not (distinct found 0))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {forall _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {(= found 0)};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {(not (distinct found 0))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {forall _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element));
 {(< i n)} || {(>= i n)};
 {(distinct found 0)} || {(>= i n)};
 {(< pos n)} || {(>= i n)};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {(>= i n)};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {(>= i n)};
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {(= found 1)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 
----------[B10]-> [B9] out -------:
(= n 100000);
 (distinct found 0);
 (< pos n);
 exist _i0 in [0,1,n),(= (select vectorx _i0) element);
 exist _i0 in [0,1,100000),(= (select vectorx _i0) element);
 forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element));
 {(< i n)} || {(>= i n)};
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {(= found 1)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 
----------[B10]-> [B5] out -------:
(= n 100000);
 (>= i n);
 (= found 0);
 {(< pos n)} || {(not (distinct found 0))};
 exist _i0 in [0,1,n),(not (= (select vectorx _i0) element));
 exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element));
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {(not (distinct found 0))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {(not (distinct found 0))};
 {forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element))} || {(not (distinct found 0))};
 forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element));
 forall _i0 in [0,1,i),(not (= (select vectorx _i0) element));
 forall _i0 in [0,1,n),(not (= (select vectorx _i0) element));
 forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element));
 
--------[B11] in ::--------
{(< pos n)} || {(= found 0)};
 (< i n);
 (= n 100000);
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {(= found 0)};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {(= found 0)};
 forall _i0 in [0,1,i),(not (= (select vectorx _i0) element));
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,(+ i 1)),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,(+ i 1)),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,pos),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,pos),(= (select vectorx _i0) element)};
 {(< pos n)} || {(not (distinct found 0))};
 {(< pos n)} || {(not (= (select vectorx i) element))};
 {(< pos n)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {forall _i0 in [0,1,(+ i 1)),(not (= (select vectorx _i0) element))};
 {(= (select vectorx i) element)} || {(not (distinct found 0))};
 {(= (select vectorx i) element)} || {(not (= (select vectorx i) element))};
 {(= (select vectorx i) element)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(= (select vectorx i) element)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(= (select vectorx i) element)} || {forall _i0 in [0,1,(+ i 1)),(not (= (select vectorx _i0) element))};
 {(= found 1)} || {(not (distinct found 0))};
 {(= found 1)} || {(not (= (select vectorx i) element))};
 {(= found 1)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(= found 1)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(= found 1)} || {forall _i0 in [0,1,(+ i 1)),(not (= (select vectorx _i0) element))};
 {(= pos i)} || {(not (distinct found 0))};
 {(= pos i)} || {(not (= (select vectorx i) element))};
 {(= pos i)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(= pos i)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(= pos i)} || {forall _i0 in [0,1,(+ i 1)),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {(not (distinct found 0))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {(not (= (select vectorx i) element))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {forall _i0 in [0,1,(+ i 1)),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {(not (distinct found 0))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {(not (= (select vectorx i) element))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {forall _i0 in [0,1,(+ i 1)),(not (= (select vectorx _i0) element))};
 {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))} || {(= i 0)};
 {forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element))} || {(not (distinct found 0))};
 {forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element))} || {(not (= (select vectorx i) element))};
 {forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element))} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element))} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,(+ i 1)),(not (= (select vectorx _i0) element))};
 
----------[B11]-> [B15] out -------:
(= n 100000);
 {(< pos n)} || {(= found 0)};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {(= found 0)};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {(= found 0)};
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,pos),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,pos),(= (select vectorx _i0) element)};
 {(< pos n)} || {(not (distinct found 0))};
 {(< pos n)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(= found 1)} || {(not (distinct found 0))};
 {(= found 1)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(= found 1)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {(not (distinct found 0))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {(not (distinct found 0))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element))} || {(not (distinct found 0))};
 {forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element))} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element))} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element));
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,(- i 1)),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,(- i 1)),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {(< pos n)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {(= found 1)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 
--------[B12] in ::--------
(= n 100000);
 (< i n);
 (not (distinct found 0));
 (= (select vectorx i) element);
 {(< pos n)} || {(= found 0)};
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 forall _i0 in [0,1,i),(not (= (select vectorx _i0) element));
 {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))} || {(= found 0)};
 {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))} || {(= i 0)};
 exist _i0 in [0,1,n),(= (select vectorx _i0) element);
 exist _i0 in [0,1,100000),(= (select vectorx _i0) element);
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,(+ i 1)),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,(+ i 1)),(= (select vectorx _i0) element)};
 
----------[B12]-> [B11] out -------:
(< pos n);
 (< i n);
 (= n 100000);
 (= (select vectorx i) element);
 (= found 1);
 (= pos i);
 exist _i0 in [0,1,n),(= (select vectorx _i0) element);
 exist _i0 in [0,1,100000),(= (select vectorx _i0) element);
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 forall _i0 in [0,1,i),(not (= (select vectorx _i0) element));
 {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))} || {(= i 0)};
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,(+ i 1)),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,(+ i 1)),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,pos),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,pos),(= (select vectorx _i0) element)};
 forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element));
 
--------[B13] in ::--------
(= n 100000);
 (< i n);
 (not (distinct found 0));
 {(< pos n)} || {(= found 0)};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {(= found 0)};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {(= found 0)};
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 forall _i0 in [0,1,i),(not (= (select vectorx _i0) element));
 {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))} || {(= found 0)};
 {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))} || {(= i 0)};
 
----------[B13]-> [B12] out -------:
(= n 100000);
 (< i n);
 (not (distinct found 0));
 (= (select vectorx i) element);
 {(< pos n)} || {(= found 0)};
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 forall _i0 in [0,1,i),(not (= (select vectorx _i0) element));
 {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))} || {(= found 0)};
 {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))} || {(= i 0)};
 exist _i0 in [0,1,n),(= (select vectorx _i0) element);
 exist _i0 in [0,1,100000),(= (select vectorx _i0) element);
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,(+ i 1)),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,(+ i 1)),(= (select vectorx _i0) element)};
 
----------[B13]-> [B11] out -------:
(= n 100000);
 (< i n);
 (not (distinct found 0));
 (not (= (select vectorx i) element));
 {(< pos n)} || {(= found 0)};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {(= found 0)};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {(= found 0)};
 forall _i0 in [0,1,i),(not (= (select vectorx _i0) element));
 {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))} || {(= found 0)};
 {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))} || {(= i 0)};
 exist _i0 in [0,1,n),(not (= (select vectorx _i0) element));
 exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element));
 forall _i0 in [0,1,(+ i 1)),(not (= (select vectorx _i0) element));
 
--------[B14] in ::--------
(= n 100000);
 (< i n);
 {(< pos n)} || {(= found 0)};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {(= found 0)};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {(= found 0)};
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {(< pos n)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {(= found 1)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))} || {(= found 0)};
 {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))} || {(= i 0)};
 
----------[B14]-> [B13] out -------:
(= n 100000);
 (< i n);
 (not (distinct found 0));
 {(< pos n)} || {(= found 0)};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {(= found 0)};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {(= found 0)};
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 forall _i0 in [0,1,i),(not (= (select vectorx _i0) element));
 {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))} || {(= found 0)};
 {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))} || {(= i 0)};
 
----------[B14]-> [B10] out -------:
(= n 100000);
 (< i n);
 (distinct found 0);
 (< pos n);
 exist _i0 in [0,1,n),(= (select vectorx _i0) element);
 exist _i0 in [0,1,100000),(= (select vectorx _i0) element);
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {(= found 1)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element));
 
--------[B15] in ::--------
(= n 100000);
 {(< pos n)} || {(= found 0)};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {(= found 0)};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {(= found 0)};
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {(< pos n)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {(= found 1)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))} || {(= found 0)};
 {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))} || {(= i 0)};
 
----------[B15]-> [B14] out -------:
(= n 100000);
 (< i n);
 {(< pos n)} || {(= found 0)};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {(= found 0)};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {(= found 0)};
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {(< pos n)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {(= found 1)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))} || {(= found 0)};
 {forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element))} || {(= i 0)};
 
----------[B15]-> [B10] out -------:
(= n 100000);
 (>= i n);
 {(< pos n)} || {(= found 0)};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {(= found 0)};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {(= found 0)};
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,pos),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,pos),(= (select vectorx _i0) element)};
 {(< pos n)} || {(not (distinct found 0))};
 {(< pos n)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(= found 1)} || {(not (distinct found 0))};
 {(= found 1)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(= found 1)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {(not (distinct found 0))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {(not (distinct found 0))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element))} || {(not (distinct found 0))};
 {forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element))} || {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element))} || {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 forall _i0 in [0,1,(- i 1)),(not (= (select vectorx _i0) element));
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,(- i 1)),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,(- i 1)),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(= (select vectorx _i0) element)};
 {(< pos n)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {(= found 1)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {forall _i0 in [0,1,pos),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,i),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,n),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,n),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,100000),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,n),(= (select vectorx _i0) element)};
 {exist _i0 in [0,1,100000),(not (= (select vectorx _i0) element))} || {forall _i0 in [0,1,100000),(= (select vectorx _i0) element)};
 {(< pos n)} || {forall _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(< pos n)} || {forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {(= found 1)} || {forall _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {(= found 1)} || {forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {forall _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,n),(= (select vectorx _i0) element)} || {forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {forall _i0 in [0,1,n),(not (= (select vectorx _i0) element))};
 {exist _i0 in [0,1,100000),(= (select vectorx _i0) element)} || {forall _i0 in [0,1,100000),(not (= (select vectorx _i0) element))};
 
--------[B16] in ::--------

----------[B16]-> [B15] out -------:
(= n 100000);
 (= found 0);
 (= i 0);
 
--------[B17] in ::--------

----------[B17]-> [B16] out -------:

