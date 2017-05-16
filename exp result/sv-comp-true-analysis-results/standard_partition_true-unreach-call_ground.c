*******************process function::  main***************
--------[B0] in ::--------
(>= a 100000);
 (>= x b);
 (= _ret 0);
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,c),(< (select cc _i0) 0);
 forall _i1 in [0,1,c),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {(= c 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(<= 0 (select aa _i0))};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- c 1)),(< (select cc _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {forall _i1 in [0,1,(- c 1)),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 forall _i0 in [0,1,a),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {forall _i0 in [0,1,(- x 1)),(<= 0 (select bb _i0))} || {(= x 0)};
 {forall _i1 in [0,1,(- x 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {(= x 0)};
 
--------[B1] in ::--------
(>= a 100000);
 (>= x b);
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,c),(< (select cc _i0) 0);
 forall _i1 in [0,1,c),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {(= c 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(<= 0 (select aa _i0))};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- c 1)),(< (select cc _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {forall _i1 in [0,1,(- c 1)),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 forall _i0 in [0,1,a),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {forall _i0 in [0,1,(- x 1)),(<= 0 (select bb _i0))} || {(= x 0)};
 {forall _i1 in [0,1,(- x 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {(= x 0)};
 
----------[B1]-> [B0] out -------:
(>= a 100000);
 (>= x b);
 (= _ret 0);
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,c),(< (select cc _i0) 0);
 forall _i1 in [0,1,c),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {(= c 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(<= 0 (select aa _i0))};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- c 1)),(< (select cc _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {forall _i1 in [0,1,(- c 1)),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 forall _i0 in [0,1,a),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {forall _i0 in [0,1,(- x 1)),(<= 0 (select bb _i0))} || {(= x 0)};
 {forall _i1 in [0,1,(- x 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {(= x 0)};
 
--------[B2] in ::--------
(>= a 100000);
 (< x b);
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,c),(< (select cc _i0) 0);
 forall _i1 in [0,1,c),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {(= c 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(<= 0 (select aa _i0))};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- c 1)),(< (select cc _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {forall _i1 in [0,1,(- c 1)),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 forall _i0 in [0,1,a),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {forall _i0 in [0,1,(- x 1)),(<= 0 (select bb _i0))} || {(= x 0)};
 {forall _i1 in [0,1,(- x 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {(= x 0)};
 forall _i0 in [0,1,x],(<= 0 (select bb _i0));
 forall _i1 in [0,1,x],exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 
----------[B2]-> [B3] out -------:
(>= a 100000);
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,c),(< (select cc _i0) 0);
 forall _i1 in [0,1,c),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {(= c 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(<= 0 (select aa _i0))};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- c 1)),(< (select cc _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {forall _i1 in [0,1,(- c 1)),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 forall _i0 in [0,1,a),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 forall _i0 in [0,1,(- x 1)),(<= 0 (select bb _i0));
 forall _i1 in [0,1,(- x 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 
--------[B3] in ::--------
(>= a 100000);
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,c),(< (select cc _i0) 0);
 forall _i1 in [0,1,c),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {(= c 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(<= 0 (select aa _i0))};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- c 1)),(< (select cc _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {forall _i1 in [0,1,(- c 1)),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 forall _i0 in [0,1,a),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {forall _i0 in [0,1,(- x 1)),(<= 0 (select bb _i0))} || {(= x 0)};
 {forall _i1 in [0,1,(- x 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {(= x 0)};
 
----------[B3]-> [B2] out -------:
(>= a 100000);
 (< x b);
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,c),(< (select cc _i0) 0);
 forall _i1 in [0,1,c),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {(= c 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(<= 0 (select aa _i0))};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- c 1)),(< (select cc _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {forall _i1 in [0,1,(- c 1)),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 forall _i0 in [0,1,a),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {forall _i0 in [0,1,(- x 1)),(<= 0 (select bb _i0))} || {(= x 0)};
 {forall _i1 in [0,1,(- x 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {(= x 0)};
 forall _i0 in [0,1,x],(<= 0 (select bb _i0));
 forall _i1 in [0,1,x],exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 
----------[B3]-> [B1] out -------:
(>= a 100000);
 (>= x b);
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,c),(< (select cc _i0) 0);
 forall _i1 in [0,1,c),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {(= c 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(<= 0 (select aa _i0))};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- c 1)),(< (select cc _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {forall _i1 in [0,1,(- c 1)),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 forall _i0 in [0,1,a),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {forall _i0 in [0,1,(- x 1)),(<= 0 (select bb _i0))} || {(= x 0)};
 {forall _i1 in [0,1,(- x 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {(= x 0)};
 
--------[B4] in ::--------
(>= a 100000);
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {(= c 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(<= 0 (select aa _i0))};
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,c),(< (select cc _i0) 0);
 forall _i1 in [0,1,c),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- c 1)),(< (select cc _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {forall _i1 in [0,1,(- c 1)),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 forall _i0 in [0,1,a),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 
----------[B4]-> [B3] out -------:
(>= a 100000);
 (= x 0);
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {(= c 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(<= 0 (select aa _i0))};
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,c),(< (select cc _i0) 0);
 forall _i1 in [0,1,c),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- c 1)),(< (select cc _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {forall _i1 in [0,1,(- c 1)),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 forall _i0 in [0,1,a),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 
--------[B5] in ::--------
{exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {(= c 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(<= 0 (select aa _i0))};
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,c),(< (select cc _i0) 0);
 forall _i1 in [0,1,c),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- c 1)),(< (select cc _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {forall _i1 in [0,1,(- c 1)),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 forall _i0 in [0,1,a),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 
----------[B5]-> [B9] out -------:
{exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {(= c 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(<= 0 (select aa _i0))};
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,c),(< (select cc _i0) 0);
 forall _i1 in [0,1,c),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- c 1)),(< (select cc _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {forall _i1 in [0,1,(- c 1)),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 forall _i0 in [0,1,a),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 
--------[B6] in ::--------
(< a 100000);
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {(= c 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(<= 0 (select aa _i0))};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(+ a 1)),(>= (select aa _i0) 0)};
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,c),(< (select cc _i0) 0);
 forall _i1 in [0,1,c),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,(+ a 1)),(< (select aa _i0) 0)};
 {(< (select aa a) 0)} || {(>= (select aa a) 0)};
 {(< (select aa a) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {(>= (select aa a) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 forall _i0 in [0,1,a),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)}} || {(= a 0)};
 forall _i0 in [0,1,(+ a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {forall _i0 in [0,1,(- c 1)),(< (select cc _i0) 0)} || {(>= (select aa a) 0)};
 {forall _i0 in [0,1,(- c 1)),(< (select cc _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {forall _i1 in [0,1,(- c 1)),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0))} || {(>= (select aa a) 0)};
 {forall _i1 in [0,1,(- c 1)),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 
----------[B6]-> [B5] out -------:
{exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {(= c 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(<= 0 (select aa _i0))};
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,c),(< (select cc _i0) 0);
 forall _i1 in [0,1,c),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- c 1)),(< (select cc _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {forall _i1 in [0,1,(- c 1)),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 forall _i0 in [0,1,a),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 
--------[B7] in ::--------
(< a 100000);
 (< (select aa a) 0);
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,c),(< (select cc _i0) 0);
 forall _i1 in [0,1,c),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 forall _i0 in [0,1,a),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)}} || {(= c 0)};
 {forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)}} || {(= a 0)};
 exist _i0 in [0,1,100000),(< (select aa _i0) 0);
 forall _i0 in [0,1,(+ a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,(+ a 1)),(< (select aa _i0) 0)};
 
----------[B7]-> [B6] out -------:
(< (select aa a) 0);
 (< a 100000);
 exist _i0 in [0,1,100000),(< (select aa _i0) 0);
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,a),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)}} || {(= a 0)};
 forall _i0 in [0,1,(+ a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,(+ a 1)),(< (select aa _i0) 0)};
 forall _i0 in [0,1,(- c 1)),(< (select cc _i0) 0);
 forall _i1 in [0,1,(- c 1)),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 forall _i0 in [0,1,c),(< (select cc _i0) 0);
 forall _i1 in [0,1,c),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 
--------[B8] in ::--------
(< a 100000);
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,c),(< (select cc _i0) 0);
 forall _i1 in [0,1,c),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 forall _i0 in [0,1,a),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {(= c 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(<= 0 (select aa _i0))};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)}} || {(= c 0)};
 {forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)}} || {(= a 0)};
 
----------[B8]-> [B7] out -------:
(< a 100000);
 (< (select aa a) 0);
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,c),(< (select cc _i0) 0);
 forall _i1 in [0,1,c),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 forall _i0 in [0,1,a),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)}} || {(= c 0)};
 {forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)}} || {(= a 0)};
 exist _i0 in [0,1,100000),(< (select aa _i0) 0);
 forall _i0 in [0,1,(+ a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,(+ a 1)),(< (select aa _i0) 0)};
 
----------[B8]-> [B6] out -------:
(< a 100000);
 (>= (select aa a) 0);
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,c),(< (select cc _i0) 0);
 forall _i1 in [0,1,c),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 forall _i0 in [0,1,a),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {(= c 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(<= 0 (select aa _i0))};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)}} || {(= c 0)};
 {forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)}} || {(= a 0)};
 exist _i0 in [0,1,100000),(>= (select aa _i0) 0);
 forall _i0 in [0,1,(+ a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(+ a 1)),(>= (select aa _i0) 0)};
 
--------[B9] in ::--------
forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,c),(< (select cc _i0) 0);
 forall _i1 in [0,1,c),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 forall _i0 in [0,1,a),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {(= c 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(<= 0 (select aa _i0))};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)}} || {(= c 0)};
 {forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)}} || {(= a 0)};
 
----------[B9]-> [B8] out -------:
(< a 100000);
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,c),(< (select cc _i0) 0);
 forall _i1 in [0,1,c),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 forall _i0 in [0,1,a),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {(= c 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(<= 0 (select aa _i0))};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)}} || {(= c 0)};
 {forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)}} || {(= a 0)};
 
----------[B9]-> [B4] out -------:
(>= a 100000);
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {(= c 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(<= 0 (select aa _i0))};
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,c),(< (select cc _i0) 0);
 forall _i1 in [0,1,c),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0));
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- c 1)),(< (select cc _i0) 0)} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {forall _i1 in [0,1,(- c 1)),exist _i0 in [0,1,100000),(= (select cc _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 forall _i0 in [0,1,(- a 1)),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 forall _i0 in [0,1,a),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(>= (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,100000),{(< (select aa _i0) 0)} || {(>= (select aa _i0) 0)};
 
--------[B10] in ::--------
(= c 0);
 (>= a 100000);
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,(- a 1)),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(<= 0 (select aa _i0))};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(<= 0 (select aa _i0))};
 forall _i0 in [0,1,(- a 1)),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 forall _i0 in [0,1,a),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(<= 0 (select aa _i0))};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 
----------[B10]-> [B9] out -------:
(= c 0);
 (= a 0);
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(<= 0 (select aa _i0))};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 
--------[B11] in ::--------
(= c 0);
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,(- a 1)),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(<= 0 (select aa _i0))};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(<= 0 (select aa _i0))};
 forall _i0 in [0,1,(- a 1)),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 forall _i0 in [0,1,a),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 
----------[B11]-> [B15] out -------:
(= c 0);
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,(- a 1)),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(<= 0 (select aa _i0))};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(<= 0 (select aa _i0))};
 forall _i0 in [0,1,(- a 1)),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 forall _i0 in [0,1,a),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 
--------[B12] in ::--------
(= c 0);
 (< a 100000);
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,(+ a 1)),(< (select aa _i0) 0)};
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(<= 0 (select aa _i0))};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(+ a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(+ a 1)),(<= 0 (select aa _i0))};
 {(<= 0 (select aa a))} || {(< (select aa a) 0)};
 {(<= 0 (select aa a))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(< (select aa a) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 forall _i0 in [0,1,a),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- a 1)),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)}} || {(= a 0)};
 forall _i0 in [0,1,(+ a 1)),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {(< (select aa a) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {(< (select aa a) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 
----------[B12]-> [B11] out -------:
(= c 0);
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,(- a 1)),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(<= 0 (select aa _i0))};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(<= 0 (select aa _i0))};
 forall _i0 in [0,1,(- a 1)),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 forall _i0 in [0,1,a),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 
--------[B13] in ::--------
(= c 0);
 (< a 100000);
 (>= (select aa a) 0);
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,a),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(<= 0 (select aa _i0))};
 {forall _i0 in [0,1,(- a 1)),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)}} || {(= a 0)};
 {forall _i0 in [0,1,(- a 1)),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)}} || {(= b 0)};
 exist _i0 in [0,1,100000),(>= (select aa _i0) 0);
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(+ a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(+ a 1)),(<= 0 (select aa _i0))};
 
----------[B13]-> [B12] out -------:
(<= 0 (select aa a));
 (= c 0);
 (< a 100000);
 exist _i0 in [0,1,100000),(<= 0 (select aa _i0));
 forall _i0 in [0,1,a),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(<= 0 (select aa _i0))};
 {forall _i0 in [0,1,(- a 1)),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)}} || {(= a 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(+ a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(+ a 1)),(<= 0 (select aa _i0))};
 forall _i0 in [0,1,(+ a 1)),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0));
 forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 
--------[B14] in ::--------
(= c 0);
 (< a 100000);
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,a),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(<= 0 (select aa _i0))};
 {forall _i0 in [0,1,(- a 1)),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)}} || {(= a 0)};
 {forall _i0 in [0,1,(- a 1)),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)}} || {(= b 0)};
 
----------[B14]-> [B13] out -------:
(= c 0);
 (< a 100000);
 (>= (select aa a) 0);
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,a),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(<= 0 (select aa _i0))};
 {forall _i0 in [0,1,(- a 1)),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)}} || {(= a 0)};
 {forall _i0 in [0,1,(- a 1)),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)}} || {(= b 0)};
 exist _i0 in [0,1,100000),(>= (select aa _i0) 0);
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(+ a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(+ a 1)),(<= 0 (select aa _i0))};
 
----------[B14]-> [B12] out -------:
(= c 0);
 (< a 100000);
 (< (select aa a) 0);
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,a),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- a 1)),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)}} || {(= a 0)};
 {forall _i0 in [0,1,(- a 1)),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)}} || {(= b 0)};
 exist _i0 in [0,1,100000),(< (select aa _i0) 0);
 forall _i0 in [0,1,(+ a 1)),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,(+ a 1)),(< (select aa _i0) 0)};
 
--------[B15] in ::--------
(= c 0);
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,a),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(<= 0 (select aa _i0))};
 {forall _i0 in [0,1,(- a 1)),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)}} || {(= a 0)};
 {forall _i0 in [0,1,(- a 1)),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)}} || {(= b 0)};
 
----------[B15]-> [B14] out -------:
(= c 0);
 (< a 100000);
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 forall _i0 in [0,1,a),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(<= 0 (select aa _i0))};
 {forall _i0 in [0,1,(- a 1)),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)}} || {(= a 0)};
 {forall _i0 in [0,1,(- a 1)),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)}} || {(= b 0)};
 
----------[B15]-> [B10] out -------:
(= c 0);
 (>= a 100000);
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {(= b 0)};
 forall _i0 in [0,1,b),(<= 0 (select bb _i0));
 forall _i1 in [0,1,b),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0));
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i0 in [0,1,(- b 1)),(<= 0 (select bb _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {forall _i1 in [0,1,(- b 1)),exist _i0 in [0,1,100000),(= (select bb _i1) (select aa _i0))} || {exist _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,(- a 1)),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,a),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,(- a 1)),(<= 0 (select aa _i0))};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,a),(<= 0 (select aa _i0))};
 forall _i0 in [0,1,(- a 1)),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 forall _i0 in [0,1,a),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(<= 0 (select aa _i0))} || {forall _i0 in [0,1,100000),(< (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(>= (select aa _i0) 0)};
 {exist _i0 in [0,1,100000),(< (select aa _i0) 0)} || {forall _i0 in [0,1,100000),(<= 0 (select aa _i0))};
 forall _i0 in [0,1,100000),{(<= 0 (select aa _i0))} || {(< (select aa _i0) 0)};
 
--------[B16] in ::--------

----------[B16]-> [B15] out -------:
(= a 0);
 (= b 0);
 (= c 0);
 
--------[B17] in ::--------

----------[B17]-> [B16] out -------:

