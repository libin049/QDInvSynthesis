*******************process function::  insert***************
--------[B0] in ::--------
(= _ret (+ size 1));
 
--------[B1] in ::--------

----------[B1]-> [B0] out -------:
(= _ret (+ size 1));
 
--------[B2] in ::--------

----------[B2]-> [B1] out -------:

*******************process function::  elem_exists***************
--------[B0] in ::--------
forall _i0 in [0,1,i),(not (= (def_pointer (+ set _i0)) value));
 {(>= i size)} || {(< i size)};
 {(>= i size)} || {(= (def_pointer (+ set i)) value)};
 {(>= i size)} || {(= _ret 1)};
 {(>= i size)} || {exist _i0 in [0,1,size),(= (def_pointer (+ set _i0)) value)};
 {(= _ret 0)} || {(< i size)};
 {(= _ret 0)} || {(= (def_pointer (+ set i)) value)};
 {(= _ret 0)} || {(= _ret 1)};
 {(= _ret 0)} || {exist _i0 in [0,1,size),(= (def_pointer (+ set _i0)) value)};
 {exist _i0 in [0,1,size),(not (= (def_pointer (+ set _i0)) value))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(not (= (def_pointer (+ set _i0)) value))} || {(= i 0)};
 {forall _i0 in [0,1,size),(not (= (def_pointer (+ set _i0)) value))} || {(< i size)};
 {forall _i0 in [0,1,size),(not (= (def_pointer (+ set _i0)) value))} || {(= (def_pointer (+ set i)) value)};
 {forall _i0 in [0,1,size),(not (= (def_pointer (+ set _i0)) value))} || {(= _ret 1)};
 {forall _i0 in [0,1,size),(not (= (def_pointer (+ set _i0)) value))} || {exist _i0 in [0,1,size),(= (def_pointer (+ set _i0)) value)};
 
--------[B1] in ::--------
(>= i size);
 forall _i0 in [0,1,i),(not (= (def_pointer (+ set _i0)) value));
 {exist _i0 in [0,1,size),(not (= (def_pointer (+ set _i0)) value))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(not (= (def_pointer (+ set _i0)) value))} || {(= i 0)};
 forall _i0 in [0,1,size),(not (= (def_pointer (+ set _i0)) value));
 
----------[B1]-> [B0] out -------:
(>= i size);
 (= _ret 0);
 forall _i0 in [0,1,i),(not (= (def_pointer (+ set _i0)) value));
 {exist _i0 in [0,1,size),(not (= (def_pointer (+ set _i0)) value))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(not (= (def_pointer (+ set _i0)) value))} || {(= i 0)};
 forall _i0 in [0,1,size),(not (= (def_pointer (+ set _i0)) value));
 
--------[B2] in ::--------
(< i size);
 (not (= (def_pointer (+ set i)) value));
 forall _i0 in [0,1,i),(not (= (def_pointer (+ set _i0)) value));
 {forall _i0 in [0,1,(- i 1)),(not (= (def_pointer (+ set _i0)) value))} || {(= i 0)};
 exist _i0 in [0,1,size),(not (= (def_pointer (+ set _i0)) value));
 forall _i0 in [0,1,(+ i 1)),(not (= (def_pointer (+ set _i0)) value));
 
----------[B2]-> [B5] out -------:
exist _i0 in [0,1,size),(not (= (def_pointer (+ set _i0)) value));
 forall _i0 in [0,1,(- i 1)),(not (= (def_pointer (+ set _i0)) value));
 forall _i0 in [0,1,i),(not (= (def_pointer (+ set _i0)) value));
 
--------[B3] in ::--------
(< i size);
 (= (def_pointer (+ set i)) value);
 forall _i0 in [0,1,i),(not (= (def_pointer (+ set _i0)) value));
 {exist _i0 in [0,1,size),(not (= (def_pointer (+ set _i0)) value))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(not (= (def_pointer (+ set _i0)) value))} || {(= i 0)};
 exist _i0 in [0,1,size),(= (def_pointer (+ set _i0)) value);
 
----------[B3]-> [B0] out -------:
(< i size);
 (= (def_pointer (+ set i)) value);
 (= _ret 1);
 exist _i0 in [0,1,size),(= (def_pointer (+ set _i0)) value);
 forall _i0 in [0,1,i),(not (= (def_pointer (+ set _i0)) value));
 {exist _i0 in [0,1,size),(not (= (def_pointer (+ set _i0)) value))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(not (= (def_pointer (+ set _i0)) value))} || {(= i 0)};
 
--------[B4] in ::--------
(< i size);
 forall _i0 in [0,1,i),(not (= (def_pointer (+ set _i0)) value));
 {exist _i0 in [0,1,size),(not (= (def_pointer (+ set _i0)) value))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(not (= (def_pointer (+ set _i0)) value))} || {(= i 0)};
 
----------[B4]-> [B3] out -------:
(< i size);
 (= (def_pointer (+ set i)) value);
 forall _i0 in [0,1,i),(not (= (def_pointer (+ set _i0)) value));
 {exist _i0 in [0,1,size),(not (= (def_pointer (+ set _i0)) value))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(not (= (def_pointer (+ set _i0)) value))} || {(= i 0)};
 exist _i0 in [0,1,size),(= (def_pointer (+ set _i0)) value);
 
----------[B4]-> [B2] out -------:
(< i size);
 (not (= (def_pointer (+ set i)) value));
 forall _i0 in [0,1,i),(not (= (def_pointer (+ set _i0)) value));
 {forall _i0 in [0,1,(- i 1)),(not (= (def_pointer (+ set _i0)) value))} || {(= i 0)};
 exist _i0 in [0,1,size),(not (= (def_pointer (+ set _i0)) value));
 forall _i0 in [0,1,(+ i 1)),(not (= (def_pointer (+ set _i0)) value));
 
--------[B5] in ::--------
forall _i0 in [0,1,i),(not (= (def_pointer (+ set _i0)) value));
 {exist _i0 in [0,1,size),(not (= (def_pointer (+ set _i0)) value))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(not (= (def_pointer (+ set _i0)) value))} || {(= i 0)};
 
----------[B5]-> [B4] out -------:
(< i size);
 forall _i0 in [0,1,i),(not (= (def_pointer (+ set _i0)) value));
 {exist _i0 in [0,1,size),(not (= (def_pointer (+ set _i0)) value))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(not (= (def_pointer (+ set _i0)) value))} || {(= i 0)};
 
----------[B5]-> [B1] out -------:
(>= i size);
 forall _i0 in [0,1,i),(not (= (def_pointer (+ set _i0)) value));
 {exist _i0 in [0,1,size),(not (= (def_pointer (+ set _i0)) value))} || {(= i 0)};
 {forall _i0 in [0,1,(- i 1)),(not (= (def_pointer (+ set _i0)) value))} || {(= i 0)};
 forall _i0 in [0,1,size),(not (= (def_pointer (+ set _i0)) value));
 
--------[B6] in ::--------

----------[B6]-> [B5] out -------:
(= i 0);
 
--------[B7] in ::--------

----------[B7]-> [B6] out -------:

*******************process function::  main***************
--------[B0] in ::--------
(>= v 100000);
 (>= x n);
 (= _ret 0);
 {(>= y n)} || {(= x 0)};
 
--------[B1] in ::--------
(>= v 100000);
 (>= x n);
 {(>= y n)} || {(= x 0)};
 
----------[B1]-> [B0] out -------:
(>= v 100000);
 (>= x n);
 (= _ret 0);
 {(>= y n)} || {(= x 0)};
 
--------[B2] in ::--------
(>= v 100000);
 (< x n);
 (< x y);
 (>= y n);
 
----------[B2]-> [B6] out -------:
(>= v 100000);
 (>= y n);
 
--------[B3] in ::--------
(>= v 100000);
 (< x n);
 (< y n);
 
----------[B3]-> [B4] out -------:
(>= v 100000);
 (< x n);
 
--------[B4] in ::--------
(>= v 100000);
 (< x n);
 
----------[B4]-> [B3] out -------:
(>= v 100000);
 (< x n);
 (< y n);
 
----------[B4]-> [B2] out -------:
(>= v 100000);
 (< x n);
 (< x y);
 (>= y n);
 
--------[B5] in ::--------
(>= v 100000);
 (< x n);
 {(>= y n)} || {(= x 0)};
 
----------[B5]-> [B4] out -------:
(>= v 100000);
 (< x n);
 (= y (+ x 1));
 
--------[B6] in ::--------
(>= v 100000);
 {(>= y n)} || {(= x 0)};
 
----------[B6]-> [B5] out -------:
(>= v 100000);
 (< x n);
 {(>= y n)} || {(= x 0)};
 
----------[B6]-> [B1] out -------:
(>= v 100000);
 (>= x n);
 {(>= y n)} || {(= x 0)};
 
--------[B7] in ::--------
(>= x n);
 (>= v 100000);
 {(>= y n)} || {(= x 0)};
 
----------[B7]-> [B6] out -------:
(>= v 100000);
 (= x 0);
 
--------[B8] in ::--------
(< v 100000);
 (>= x n);
 {(>= y n)} || {(= x 0)};
 
----------[B8]-> [B17] out -------:
(>= x n);
 {(>= y n)} || {(= x 0)};
 
--------[B9] in ::--------
(< v 100000);
 (< x n);
 (< x y);
 (>= y n);
 
----------[B9]-> [B13] out -------:
(< v 100000);
 (>= y n);
 
--------[B10] in ::--------
(< v 100000);
 (< x n);
 (< y n);
 
----------[B10]-> [B11] out -------:
(< v 100000);
 (< x n);
 
--------[B11] in ::--------
(< v 100000);
 (< x n);
 
----------[B11]-> [B10] out -------:
(< v 100000);
 (< x n);
 (< y n);
 
----------[B11]-> [B9] out -------:
(< v 100000);
 (< x n);
 (< x y);
 (>= y n);
 
--------[B12] in ::--------
(< v 100000);
 (< x n);
 {(>= y n)} || {(= x 0)};
 
----------[B12]-> [B11] out -------:
(< v 100000);
 (< x n);
 (= y (+ x 1));
 
--------[B13] in ::--------
(< v 100000);
 {(>= y n)} || {(= x 0)};
 
----------[B13]-> [B12] out -------:
(< v 100000);
 (< x n);
 {(>= y n)} || {(= x 0)};
 
----------[B13]-> [B8] out -------:
(< v 100000);
 (>= x n);
 {(>= y n)} || {(= x 0)};
 
--------[B14] in ::--------
(< v 100000);
 
----------[B14]-> [B13] out -------:
(< v 100000);
 (= x 0);
 
--------[B15] in ::--------
(>= x n);
 (< v 100000);
 (distinct (elem_exists set n (select values v)) 0);
 {(>= y n)} || {(= x 0)};
 exist _i0 in [0,1,100000),(distinct (elem_exists set n (select values _i0)) 0);
 
----------[B15]-> [B14] out -------:
(< v 100000);
 
--------[B16] in ::--------
(>= x n);
 (< v 100000);
 {(>= y n)} || {(= x 0)};
 
----------[B16]-> [B15] out -------:
(>= x n);
 (< v 100000);
 (distinct (elem_exists set n (select values v)) 0);
 {(>= y n)} || {(= x 0)};
 exist _i0 in [0,1,100000),(distinct (elem_exists set n (select values _i0)) 0);
 
----------[B16]-> [B14] out -------:
(>= x n);
 (< v 100000);
 (= (elem_exists set n (select values v)) 0);
 {(>= y n)} || {(= x 0)};
 exist _i0 in [0,1,100000),(= (elem_exists set n (select values _i0)) 0);
 
--------[B17] in ::--------
(>= x n);
 {(>= y n)} || {(= x 0)};
 
----------[B17]-> [B16] out -------:
(>= x n);
 (< v 100000);
 {(>= y n)} || {(= x 0)};
 
----------[B17]-> [B7] out -------:
(>= x n);
 (>= v 100000);
 {(>= y n)} || {(= x 0)};
 
--------[B18] in ::--------
(>= x n);
 {(>= y n)} || {(= n 0)};
 {(>= y n)} || {(= x 0)};
 
----------[B18]-> [B17] out -------:
(>= x n);
 (= v 0);
 {(>= y n)} || {(= n 0)};
 {(>= y n)} || {(= x 0)};
 
--------[B19] in ::--------
(< x n);
 (< x y);
 (>= y n);
 
----------[B19]-> [B23] out -------:
(>= y n);
 
--------[B20] in ::--------
(< x n);
 (< y n);
 
----------[B20]-> [B21] out -------:
(< x n);
 
--------[B21] in ::--------
(< x n);
 
----------[B21]-> [B20] out -------:
(< x n);
 (< y n);
 
----------[B21]-> [B19] out -------:
(< x n);
 (< x y);
 (>= y n);
 
--------[B22] in ::--------
(>= y n);
 (< x y);
 (< x n);
 
----------[B22]-> [B21] out -------:
(< x n);
 (= y (+ x 1));
 
--------[B23] in ::--------
{(>= y n)} || {(= n 0)};
 {(>= y n)} || {(= x 0)};
 
----------[B23]-> [B22] out -------:
(>= y n);
 (< x y);
 (< x n);
 
----------[B23]-> [B18] out -------:
(>= x n);
 {(>= y n)} || {(= n 0)};
 {(>= y n)} || {(= x 0)};
 
--------[B24] in ::--------

----------[B24]-> [B23] out -------:
(= n 0);
 (= x 0);
 
--------[B25] in ::--------

----------[B25]-> [B24] out -------:

