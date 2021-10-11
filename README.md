# Compiling C at runtime using the Tiny C Compiler

## Overview
Tiny C Compiler (tcc) allows runtime C compilation.
Using it as a library (libtcc), we can compile C code and access its compiled symbols at runtime.
The goal of this exercise is to tie it together with a bit of C++ to demonstrate how it would fare in a C++ codebase.


## Demonstrated features
* runtime C code compilation
* expose C++ code as extern C code and call it from the runtime-compiled script
* ExternalProject setup for tcc


## Instructions
```sh
mkdir build; cd build
cmake .. && make && make install

# launch the demo binary
bin/tinyccdemo ../scripts/cscript.c
```
