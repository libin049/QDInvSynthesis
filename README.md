# QDInvSynthesis

this is the tool for "A Framework for Array Invariants Synthesis in Induction-loop Programs".
We offer a binares file, which can be executed in ubuntu 64bit(>= 14.04).

##Execute:
./main ../array.cpp --

If it can not be executed in your linux system. you can build it.

##build
Building QDInvSynthesis using Z3 and Clang

1. you must build Z3 in your system. please see it in https://github.com/Z3Prover/z3

2. you must build clang(>=3.6.2) in your system. please see it in http://clang.llvm.org/get_started.html.

3. cd src, edit compile.sh, set LLVM_SRC_PATH, LLVM_BUILD_PATH, LLVM_BIN_PATH, z3_src_path and z3_build_path

4. run compile.sh,  cd src, Execute:  ./main ../array.cpp --
