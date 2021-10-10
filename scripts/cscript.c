#include <stdio.h>
#include <cpplib.h>

const char* tccCompiledCFunction()
{
  printf("Executing TCC-generated C function\n");
  return externC_cppFunction();
}

