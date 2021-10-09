#include <stdio.h>
#include <cpplib.h>
#include <assert.h>

void cfunction(const char* msg)
{
  const char* newMsg = append_cpp_message(msg);
  printf(newMsg);
}

