*******************process function::  is_relaxed_prefix***************
--------[B0] in ::--------
{(= _ret 1)} || {(= _ret 0)};
 {(<= pat_length (+ a_length 1))} || {(> pat_length (+ a_length 1))};
 {(<= pat_length (+ a_length 1))} || {(= _ret 0)};
 
--------[B1] in ::--------
(<= pat_length (+ a_length 1));
 {(= shift 1)} || {(= shift 0)};
 {(= shift 1)} || {forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 {(< i (+ a_length 1))} || {(>= i pat_length)};
 {(< i pat_length)} || {(>= i pat_length)};
 {(< a_length pat_length)} || {(>= i pat_length)};
 {(>= i a_length)} || {(>= i pat_length)};
 {(< a_length (+ a_length 1))} || {(>= i pat_length)};
 {(< a_length (+ a_length 1))} || {(<= pat_length a_length)};
 {(> pat_length a_length)} || {(>= i pat_length)};
 {(> pat_length a_length)} || {(<= pat_length a_length)};
 {(not (= shift 1))} || {(>= i pat_length)};
 {(not (= shift 1))} || {(<= pat_length a_length)};
 {(= shift 0)} || {(>= i pat_length)};
 {(= shift 0)} || {(<= pat_length a_length)};
 {forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))} || {(>= i pat_length)};
 {forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))} || {(<= pat_length a_length)};
 
----------[B1]-> [B0] out -------:
(<= pat_length (+ a_length 1));
 (= _ret 1);
 {(= shift 1)} || {(= shift 0)};
 {(= shift 1)} || {forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 {(< i (+ a_length 1))} || {(>= i pat_length)};
 {(< i pat_length)} || {(>= i pat_length)};
 {(< a_length pat_length)} || {(>= i pat_length)};
 {(>= i a_length)} || {(>= i pat_length)};
 {(< a_length (+ a_length 1))} || {(>= i pat_length)};
 {(< a_length (+ a_length 1))} || {(<= pat_length a_length)};
 {(> pat_length a_length)} || {(>= i pat_length)};
 {(> pat_length a_length)} || {(<= pat_length a_length)};
 {(not (= shift 1))} || {(>= i pat_length)};
 {(not (= shift 1))} || {(<= pat_length a_length)};
 {(= shift 0)} || {(>= i pat_length)};
 {(= shift 0)} || {(<= pat_length a_length)};
 {forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))} || {(>= i pat_length)};
 {forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))} || {(<= pat_length a_length)};
 
--------[B2] in ::--------
(<= pat_length (+ a_length 1));
 (< a_length (+ a_length 1));
 (> pat_length a_length);
 (= shift 1);
 {(< i (+ a_length 1))} || {(>= i pat_length)};
 {(< i pat_length)} || {(>= i pat_length)};
 {(< a_length pat_length)} || {(>= i pat_length)};
 {(>= i a_length)} || {(>= i pat_length)};
 
----------[B2]-> [B0] out -------:
(<= pat_length (+ a_length 1));
 (< a_length (+ a_length 1));
 (> pat_length a_length);
 (= shift 1);
 (= _ret 0);
 {(< i (+ a_length 1))} || {(>= i pat_length)};
 {(< i pat_length)} || {(>= i pat_length)};
 {(< a_length pat_length)} || {(>= i pat_length)};
 {(>= i a_length)} || {(>= i pat_length)};
 
--------[B3] in ::--------
(<= pat_length (+ a_length 1));
 (< a_length (+ a_length 1));
 (> pat_length a_length);
 {(< i (+ a_length 1))} || {(>= i pat_length)};
 {(< i pat_length)} || {(>= i pat_length)};
 {(< a_length pat_length)} || {(>= i pat_length)};
 {(>= i a_length)} || {(>= i pat_length)};
 {(= shift 1)} || {(= shift 0)};
 {(= shift 1)} || {forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 
----------[B3]-> [B2] out -------:
(<= pat_length (+ a_length 1));
 (< a_length (+ a_length 1));
 (> pat_length a_length);
 (= shift 1);
 {(< i (+ a_length 1))} || {(>= i pat_length)};
 {(< i pat_length)} || {(>= i pat_length)};
 {(< a_length pat_length)} || {(>= i pat_length)};
 {(>= i a_length)} || {(>= i pat_length)};
 
----------[B3]-> [B1] out -------:
(<= pat_length (+ a_length 1));
 (< a_length (+ a_length 1));
 (> pat_length a_length);
 (not (= shift 1));
 {(< i (+ a_length 1))} || {(>= i pat_length)};
 {(< i pat_length)} || {(>= i pat_length)};
 {(< a_length pat_length)} || {(>= i pat_length)};
 {(>= i a_length)} || {(>= i pat_length)};
 (= shift 0);
 forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 
--------[B4] in ::--------
(<= pat_length (+ a_length 1));
 {(< i (+ a_length 1))} || {(>= i pat_length)};
 {(< i pat_length)} || {(>= i pat_length)};
 {(< a_length (+ a_length 1))} || {(>= i pat_length)};
 {(< a_length pat_length)} || {(>= i pat_length)};
 {(>= i a_length)} || {(>= i pat_length)};
 {(= shift 1)} || {(= shift 0)};
 {(= shift 1)} || {forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 
----------[B4]-> [B3] out -------:
(<= pat_length (+ a_length 1));
 (< a_length (+ a_length 1));
 (> pat_length a_length);
 {(< i (+ a_length 1))} || {(>= i pat_length)};
 {(< i pat_length)} || {(>= i pat_length)};
 {(< a_length pat_length)} || {(>= i pat_length)};
 {(>= i a_length)} || {(>= i pat_length)};
 {(= shift 1)} || {(= shift 0)};
 {(= shift 1)} || {forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 
----------[B4]-> [B1] out -------:
(<= pat_length (+ a_length 1));
 (>= i pat_length);
 (<= pat_length a_length);
 {(= shift 1)} || {(= shift 0)};
 {(= shift 1)} || {forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 {(= shift 1)} || {forall _i0 in [0,1,pat_length),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 
--------[B5] in ::--------
(<= pat_length (+ a_length 1));
 (< i (+ a_length 1));
 (< i pat_length);
 (< i a_length);
 {(= shift 1)} || {(= shift 0)};
 {(= shift 1)} || {forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 {(= shift 1)} || {forall _i0 in [0,1,(+ i 1)),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 {(= shift 1)} || {(= (def_pointer (+ pat i)) (def_pointer (+ a (- i shift))))};
 {(= shift 1)} || {exist _i0 in [0,1,pat_length),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 {(= shift 1)} || {exist _i0 in [0,1,(+ a_length 1)),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 {(= shift 1)} || {exist _i0 in [0,1,a_length),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 
----------[B5]-> [B11] out -------:
(<= pat_length (+ a_length 1));
 {(= shift 1)} || {(= shift 0)};
 {(= shift 1)} || {exist _i0 in [0,1,pat_length),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 {(= shift 1)} || {exist _i0 in [0,1,(+ a_length 1)),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 {(= shift 1)} || {exist _i0 in [0,1,a_length),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 {(= shift 1)} || {forall _i0 in [0,1,(- i 1)),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 {(= shift 1)} || {forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 
--------[B6] in ::--------
(<= pat_length (+ a_length 1));
 (< i (+ a_length 1));
 (< i pat_length);
 (< i a_length);
 (distinct (def_pointer (+ pat i)) (def_pointer (+ a (- i shift))));
 (not (= shift 0));
 (= shift 1);
 exist _i0 in [0,1,pat_length),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 exist _i0 in [0,1,(+ a_length 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 exist _i0 in [0,1,a_length),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 
----------[B6]-> [B0] out -------:
(<= pat_length (+ a_length 1));
 (< i (+ a_length 1));
 (< i pat_length);
 (< i a_length);
 (distinct (def_pointer (+ pat i)) (def_pointer (+ a (- i shift))));
 (not (= shift 0));
 (= shift 1);
 (= _ret 0);
 exist _i0 in [0,1,pat_length),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 exist _i0 in [0,1,(+ a_length 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 exist _i0 in [0,1,a_length),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 
--------[B7] in ::--------
(<= pat_length (+ a_length 1));
 (< i (+ a_length 1));
 (< i pat_length);
 (< i a_length);
 (distinct (def_pointer (+ pat i)) (def_pointer (+ a (- i shift))));
 (= shift 0);
 forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 exist _i0 in [0,1,pat_length),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 exist _i0 in [0,1,(+ a_length 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 exist _i0 in [0,1,a_length),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 
----------[B7]-> [B5] out -------:
(<= pat_length (+ a_length 1));
 (< i (+ a_length 1));
 (< i pat_length);
 (< i a_length);
 (= shift 1);
 
--------[B8] in ::--------
(<= pat_length (+ a_length 1));
 (< i (+ a_length 1));
 (< i pat_length);
 (< i a_length);
 (distinct (def_pointer (+ pat i)) (def_pointer (+ a (- i shift))));
 {(= shift 1)} || {(= shift 0)};
 {(= shift 1)} || {forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 exist _i0 in [0,1,pat_length),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 exist _i0 in [0,1,(+ a_length 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 exist _i0 in [0,1,a_length),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 
----------[B8]-> [B7] out -------:
(<= pat_length (+ a_length 1));
 (< i (+ a_length 1));
 (< i pat_length);
 (< i a_length);
 (distinct (def_pointer (+ pat i)) (def_pointer (+ a (- i shift))));
 (= shift 0);
 forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 exist _i0 in [0,1,pat_length),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 exist _i0 in [0,1,(+ a_length 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 exist _i0 in [0,1,a_length),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 
----------[B8]-> [B6] out -------:
(<= pat_length (+ a_length 1));
 (< i (+ a_length 1));
 (< i pat_length);
 (< i a_length);
 (distinct (def_pointer (+ pat i)) (def_pointer (+ a (- i shift))));
 (not (= shift 0));
 (= shift 1);
 exist _i0 in [0,1,pat_length),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 exist _i0 in [0,1,(+ a_length 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 exist _i0 in [0,1,a_length),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 
--------[B9] in ::--------
(<= pat_length (+ a_length 1));
 (< i (+ a_length 1));
 (< i pat_length);
 (< i a_length);
 {(= shift 1)} || {(= shift 0)};
 {(= shift 1)} || {forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 
----------[B9]-> [B8] out -------:
(<= pat_length (+ a_length 1));
 (< i (+ a_length 1));
 (< i pat_length);
 (< i a_length);
 (distinct (def_pointer (+ pat i)) (def_pointer (+ a (- i shift))));
 {(= shift 1)} || {(= shift 0)};
 {(= shift 1)} || {forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 exist _i0 in [0,1,pat_length),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 exist _i0 in [0,1,(+ a_length 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 exist _i0 in [0,1,a_length),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 
----------[B9]-> [B5] out -------:
(<= pat_length (+ a_length 1));
 (< i (+ a_length 1));
 (< i pat_length);
 (< i a_length);
 (= (def_pointer (+ pat i)) (def_pointer (+ a (- i shift))));
 {(= shift 1)} || {(= shift 0)};
 {(= shift 1)} || {forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 exist _i0 in [0,1,pat_length),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 exist _i0 in [0,1,(+ a_length 1)),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 exist _i0 in [0,1,a_length),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))));
 {(= shift 1)} || {forall _i0 in [0,1,(+ i 1)),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 
--------[B10] in ::--------
(<= pat_length (+ a_length 1));
 (< i (+ a_length 1));
 (< i pat_length);
 {(= shift 1)} || {(= shift 0)};
 {(= shift 1)} || {forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 
----------[B10]-> [B9] out -------:
(<= pat_length (+ a_length 1));
 (< i (+ a_length 1));
 (< i pat_length);
 (< i a_length);
 {(= shift 1)} || {(= shift 0)};
 {(= shift 1)} || {forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 
----------[B10]-> [B4] out -------:
(<= pat_length (+ a_length 1));
 (< i (+ a_length 1));
 (< i pat_length);
 (< a_length (+ a_length 1));
 (< a_length pat_length);
 (>= i a_length);
 {(= shift 1)} || {(= shift 0)};
 {(= shift 1)} || {forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 {(= shift 1)} || {forall _i0 in [0,1,a_length),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 
--------[B11] in ::--------
(<= pat_length (+ a_length 1));
 {(= shift 1)} || {(= shift 0)};
 {(= shift 1)} || {forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 
----------[B11]-> [B10] out -------:
(<= pat_length (+ a_length 1));
 (< i (+ a_length 1));
 (< i pat_length);
 {(= shift 1)} || {(= shift 0)};
 {(= shift 1)} || {forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 
----------[B11]-> [B4] out -------:
(<= pat_length (+ a_length 1));
 (>= i pat_length);
 {(= shift 1)} || {(= shift 0)};
 {(= shift 1)} || {forall _i0 in [0,1,i),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 {(= shift 1)} || {forall _i0 in [0,1,pat_length),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 shift))))};
 
--------[B12] in ::--------
(<= pat_length (+ a_length 1));
 
----------[B12]-> [B11] out -------:
(<= pat_length (+ a_length 1));
 (= shift 0);
 (= i 0);
 
--------[B13] in ::--------
(> pat_length (+ a_length 1));
 
----------[B13]-> [B0] out -------:
(> pat_length (+ a_length 1));
 (= _ret 0);
 
--------[B14] in ::--------

----------[B14]-> [B13] out -------:
(> pat_length (+ a_length 1));
 
----------[B14]-> [B12] out -------:
(<= pat_length (+ a_length 1));
 
--------[B15] in ::--------

----------[B15]-> [B14] out -------:

*******************process function::  main***************
--------[B0] in ::--------
(= _ret 0);
 
--------[B1] in ::--------

----------[B1]-> [B0] out -------:
(= _ret 0);
 
--------[B2] in ::--------
(<= pat_len (+ a_len 1));
 (< a_len (+ a_len 1));
 (> pat_len a_len);
 forall _i1 in [0,1,differences),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 {(< i2 (+ a_len 1))} || {(>= i2 pat_len)};
 {(< i2 pat_len)} || {(>= i2 pat_len)};
 {(< a_len pat_len)} || {(>= i2 pat_len)};
 {(>= i2 a_len)} || {(>= i2 pat_len)};
 
----------[B2]-> [B1] out -------:
(<= pat_len (+ a_len 1));
 (< a_len (+ a_len 1));
 (> pat_len a_len);
 {(< i2 (+ a_len 1))} || {(>= i2 pat_len)};
 {(< i2 pat_len)} || {(>= i2 pat_len)};
 {(< a_len pat_len)} || {(>= i2 pat_len)};
 {(>= i2 a_len)} || {(>= i2 pat_len)};
 forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 
--------[B3] in ::--------
(<= pat_len (+ a_len 1));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 {(< i2 (+ a_len 1))} || {(>= i2 pat_len)};
 {(< i2 pat_len)} || {(>= i2 pat_len)};
 {(< a_len (+ a_len 1))} || {(>= i2 pat_len)};
 {(< a_len pat_len)} || {(>= i2 pat_len)};
 {(>= i2 a_len)} || {(>= i2 pat_len)};
 
----------[B3]-> [B2] out -------:
(<= pat_len (+ a_len 1));
 (< a_len (+ a_len 1));
 (> pat_len a_len);
 forall _i1 in [0,1,differences),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 {(< i2 (+ a_len 1))} || {(>= i2 pat_len)};
 {(< i2 pat_len)} || {(>= i2 pat_len)};
 {(< a_len pat_len)} || {(>= i2 pat_len)};
 {(>= i2 a_len)} || {(>= i2 pat_len)};
 
----------[B3]-> [B1] out -------:
(<= pat_len (+ a_len 1));
 (>= i2 pat_len);
 (<= pat_len a_len);
 forall _i1 in [0,1,differences),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 
--------[B4] in ::--------
(<= pat_len (+ a_len 1));
 (< i2 (+ a_len 1));
 (< i2 pat_len);
 (< i2 a_len);
 forall _i1 in [0,1,differences),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 {forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))))} || {(= (def_pointer (+ pat i2)) (def_pointer (+ a (- i2 differences))))};
 {forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))))} || {exist _i0 in [0,1,pat_len),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))))};
 {forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))))} || {exist _i0 in [0,1,(+ a_len 1)),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))))};
 {forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))))} || {exist _i0 in [0,1,a_len),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))))};
 {forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))))} || {(= (def_pointer (+ pat i2)) (def_pointer (+ a (- i2 differences))))};
 {forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))))} || {exist _i0 in [0,1,pat_len),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))))};
 {forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))))} || {exist _i0 in [0,1,(+ a_len 1)),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))))};
 {forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))))} || {exist _i0 in [0,1,a_len),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))))};
 {forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))))} || {(= (def_pointer (+ pat i2)) (def_pointer (+ a (- i2 differences))))};
 {forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))))} || {exist _i0 in [0,1,pat_len),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))))};
 {forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))))} || {exist _i0 in [0,1,(+ a_len 1)),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))))};
 {forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))))} || {exist _i0 in [0,1,a_len),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))))};
 
----------[B4]-> [B8] out -------:
(<= pat_len (+ a_len 1));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 {forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))))} || {exist _i0 in [0,1,pat_len),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))))};
 {forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))))} || {exist _i0 in [0,1,(+ a_len 1)),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))))};
 {forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))))} || {exist _i0 in [0,1,a_len),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))))};
 {forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))))} || {exist _i0 in [0,1,pat_len),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))))};
 {forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))))} || {exist _i0 in [0,1,(+ a_len 1)),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))))};
 {forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))))} || {exist _i0 in [0,1,a_len),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))))};
 {forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))))} || {exist _i0 in [0,1,pat_len),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))))};
 {forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))))} || {exist _i0 in [0,1,(+ a_len 1)),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))))};
 {forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))))} || {exist _i0 in [0,1,a_len),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))))};
 
--------[B5] in ::--------
(<= pat_len (+ a_len 1));
 (< i2 (+ a_len 1));
 (< i2 pat_len);
 (< i2 a_len);
 (distinct (def_pointer (+ pat i2)) (def_pointer (+ a (- i2 differences))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))));
 exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))));
 exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))));
 forall _i1 in [0,1,(+ differences 1)),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,(+ differences 1)),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,(+ differences 1)),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 
----------[B5]-> [B4] out -------:
(<= pat_len (+ a_len 1));
 (< i2 (+ a_len 1));
 (< i2 pat_len);
 (< i2 a_len);
 forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,(- differences 1)),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 
--------[B6] in ::--------
(<= pat_len (+ a_len 1));
 (< i2 (+ a_len 1));
 (< i2 pat_len);
 (< i2 a_len);
 forall _i1 in [0,1,differences),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 
----------[B6]-> [B5] out -------:
(<= pat_len (+ a_len 1));
 (< i2 (+ a_len 1));
 (< i2 pat_len);
 (< i2 a_len);
 (distinct (def_pointer (+ pat i2)) (def_pointer (+ a (- i2 differences))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))));
 exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))));
 exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))));
 forall _i1 in [0,1,(+ differences 1)),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,(+ differences 1)),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,(+ differences 1)),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 
----------[B6]-> [B4] out -------:
(<= pat_len (+ a_len 1));
 (< i2 (+ a_len 1));
 (< i2 pat_len);
 (< i2 a_len);
 (= (def_pointer (+ pat i2)) (def_pointer (+ a (- i2 differences))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 exist _i0 in [0,1,pat_len),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))));
 exist _i0 in [0,1,(+ a_len 1)),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))));
 exist _i0 in [0,1,a_len),(= (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 differences))));
 
--------[B7] in ::--------
(<= pat_len (+ a_len 1));
 (< i2 (+ a_len 1));
 (< i2 pat_len);
 forall _i1 in [0,1,differences),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 
----------[B7]-> [B6] out -------:
(<= pat_len (+ a_len 1));
 (< i2 (+ a_len 1));
 (< i2 pat_len);
 (< i2 a_len);
 forall _i1 in [0,1,differences),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 
----------[B7]-> [B3] out -------:
(<= pat_len (+ a_len 1));
 (< i2 (+ a_len 1));
 (< i2 pat_len);
 (< a_len (+ a_len 1));
 (< a_len pat_len);
 (>= i2 a_len);
 forall _i1 in [0,1,differences),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 
--------[B8] in ::--------
(<= pat_len (+ a_len 1));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 
----------[B8]-> [B7] out -------:
(<= pat_len (+ a_len 1));
 (< i2 (+ a_len 1));
 (< i2 pat_len);
 forall _i1 in [0,1,differences),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 
----------[B8]-> [B3] out -------:
(<= pat_len (+ a_len 1));
 (>= i2 pat_len);
 forall _i1 in [0,1,differences),exist _i0 in [0,1,pat_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,(+ a_len 1)),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 forall _i1 in [0,1,differences),exist _i0 in [0,1,a_len),(distinct (def_pointer (+ pat _i0)) (def_pointer (+ a (- _i0 _i1))));
 
--------[B9] in ::--------
(<= pat_len (+ a_len 1));
 
----------[B9]-> [B8] out -------:
(<= pat_len (+ a_len 1));
 (= differences 0);
 (= i2 0);
 
--------[B10] in ::--------

----------[B10]-> [B9] out -------:
(<= pat_len (+ a_len 1));
 
----------[B10]-> [B1] out -------:
(> pat_len (+ a_len 1));
 
--------[B11] in ::--------
(< i pat_len);
 (< i a_len);
 {(> pat_len a_len)} || {(= different __VERIFIER_nondet_ulong)};
 {(> pat_len a_len)} || {(<= pat_len a_len)};
 {(= different (- pat_len 1))} || {(= different __VERIFIER_nondet_ulong)};
 {(= different (- pat_len 1))} || {(<= pat_len a_len)};
 
----------[B11]-> [B13] out -------:
{(> pat_len a_len)} || {(= different __VERIFIER_nondet_ulong)};
 {(> pat_len a_len)} || {(<= pat_len a_len)};
 {(= different (- pat_len 1))} || {(= different __VERIFIER_nondet_ulong)};
 {(= different (- pat_len 1))} || {(<= pat_len a_len)};
 
--------[B12] in ::--------
(< i pat_len);
 {(> pat_len a_len)} || {(= different __VERIFIER_nondet_ulong)};
 {(> pat_len a_len)} || {(<= pat_len a_len)};
 {(= different (- pat_len 1))} || {(= different __VERIFIER_nondet_ulong)};
 {(= different (- pat_len 1))} || {(<= pat_len a_len)};
 
----------[B12]-> [B11] out -------:
(< i pat_len);
 (< i a_len);
 {(> pat_len a_len)} || {(= different __VERIFIER_nondet_ulong)};
 {(> pat_len a_len)} || {(<= pat_len a_len)};
 {(= different (- pat_len 1))} || {(= different __VERIFIER_nondet_ulong)};
 {(= different (- pat_len 1))} || {(<= pat_len a_len)};
 
----------[B12]-> [B1] out -------:
(< i pat_len);
 (< a_len pat_len);
 (>= i a_len);
 {(> pat_len a_len)} || {(= different __VERIFIER_nondet_ulong)};
 {(> pat_len a_len)} || {(<= pat_len a_len)};
 {(= different (- pat_len 1))} || {(= different __VERIFIER_nondet_ulong)};
 {(= different (- pat_len 1))} || {(<= pat_len a_len)};
 
--------[B13] in ::--------
{(> pat_len a_len)} || {(= different __VERIFIER_nondet_ulong)};
 {(> pat_len a_len)} || {(<= pat_len a_len)};
 {(= different (- pat_len 1))} || {(= different __VERIFIER_nondet_ulong)};
 {(= different (- pat_len 1))} || {(<= pat_len a_len)};
 
----------[B13]-> [B12] out -------:
(< i pat_len);
 {(> pat_len a_len)} || {(= different __VERIFIER_nondet_ulong)};
 {(> pat_len a_len)} || {(<= pat_len a_len)};
 {(= different (- pat_len 1))} || {(= different __VERIFIER_nondet_ulong)};
 {(= different (- pat_len 1))} || {(<= pat_len a_len)};
 
----------[B13]-> [B1] out -------:
(>= i pat_len);
 {(> pat_len a_len)} || {(= different __VERIFIER_nondet_ulong)};
 {(> pat_len a_len)} || {(<= pat_len a_len)};
 {(= different (- pat_len 1))} || {(= different __VERIFIER_nondet_ulong)};
 {(= different (- pat_len 1))} || {(<= pat_len a_len)};
 
--------[B14] in ::--------
{(> pat_len a_len)} || {(= different __VERIFIER_nondet_ulong)};
 {(> pat_len a_len)} || {(<= pat_len a_len)};
 {(= different (- pat_len 1))} || {(= different __VERIFIER_nondet_ulong)};
 {(= different (- pat_len 1))} || {(<= pat_len a_len)};
 
----------[B14]-> [B13] out -------:
(= i 0);
 {(> pat_len a_len)} || {(= different __VERIFIER_nondet_ulong)};
 {(> pat_len a_len)} || {(<= pat_len a_len)};
 {(= different (- pat_len 1))} || {(= different __VERIFIER_nondet_ulong)};
 {(= different (- pat_len 1))} || {(<= pat_len a_len)};
 
--------[B15] in ::--------
(= different __VERIFIER_nondet_ulong);
 (> pat_len a_len);
 
----------[B15]-> [B14] out -------:
(> pat_len a_len);
 (= different (- pat_len 1));
 
--------[B16] in ::--------

----------[B16]-> [B15] out -------:
(= different __VERIFIER_nondet_ulong);
 (> pat_len a_len);
 
----------[B16]-> [B14] out -------:
(= different __VERIFIER_nondet_ulong);
 (<= pat_len a_len);
 
--------[B17] in ::--------

----------[B17]-> [B16] out -------:

----------[B17]-> [B10] out -------:

--------[B18] in ::--------

----------[B18]-> [B17] out -------:

