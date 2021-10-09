#include <fstream>
#include <functional>
#include <stdio.h>
#include <cassert>
#include <iostream>

#include <libtcc.h>

int main(int argc, char **argv)
{
    TCCState* s = tcc_new();
    tcc_set_options(s, "v");
    if(!s) {
        std::cerr << "Can’t create a TCC context" << std::endl;
        return EXIT_FAILURE;
    }

    tcc_set_output_type(s, TCC_OUTPUT_MEMORY);
    tcc_add_include_path(s, "/home/g/projects/RuntimeCompiler/lib/cpplib/");
    tcc_add_library_path(s, "/home/g/projects/RuntimeCompiler/build/lib/cpplib");
    tcc_add_library(s, "cpplib");

    const std::string fpath = "/home/g/projects/RuntimeCompiler/src/encoder.c";
    std::string line,text;
    std::ifstream in(fpath);
    while(std::getline(in, line))
    {
        text += line + "\n";
    }

    if( tcc_compile_string(s, text.c_str()) < 0 )
    {
        std::cerr << "tcc_compile_string failed" << std::endl;
        return EXIT_FAILURE;
    }
    void* program { nullptr };
    program = calloc(1, tcc_relocate(s, NULL));
    if(!program)
    {
        std::cerr << "allocation failed" << std::endl;
    }

    if( tcc_relocate(s, program) < 0 ) {
        std::cerr << "tcc_relocate failed" << std::endl;
        return EXIT_FAILURE;
    }

    typedef void (*c_func_signature)(const char*);
    void* functionPointer = tcc_get_symbol(s, "cfunction");
    assert(functionPointer != nullptr);

    auto cfunction = reinterpret_cast<c_func_signature>(functionPointer);
    assert(cfunction);

    cfunction("TCC-generated C calls on cpplib::append_cpp_message");

    tcc_delete(s);

    std::cout << "success" << std::endl;
    return 0;
}

