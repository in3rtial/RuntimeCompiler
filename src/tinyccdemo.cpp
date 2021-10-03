#include "tinyccdemo.h"
#include <functional>
#include <stdio.h>
#include <libtcc.h>

// https://www.developing-stuff.com/how-to-compile-run-c-code-at-runtime-or-how-to-use-c-as-a-scripting-language/
const char* program = \
    "#include <stdio.h>"
    "int foo(const int in_value){"
    "   printf(\"this is a test: %d\n\", in_value);"
    "}";


int main(int argc, char **argv)
{
    TCCState* s = tcc_new();
    if(!s){
        printf("Can’t create a TCC context\n");
        return 1;
    }
    tcc_set_output_type(s, TCC_OUTPUT_MEMORY);

    if (tcc_compile_string(s, program) > 0) {
        printf("Compilation error !\n");
        return 2;
    }

    tcc_relocate(s, TCC_RELOCATE_AUTO);
    typedef int (*foosig)(int);
    foosig func = reinterpret_cast<foosig>(tcc_get_symbol(s, "foo"));
    func(32);

    tcc_delete(s);
    return 0;
}

