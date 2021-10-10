#include <fstream>
#include <functional>
#include <stdio.h>
#include <cassert>
#include <iostream>

#include <libtcc.h>

std::string loadCScript(const std::string& file) {
    std::string line, text;
    std::ifstream in(file);
    assert(in.good());
    while(std::getline(in, line)) {
        text += line + "\n";
    }
    return text;
}


TCCState* createTCCState() {
    TCCState* s = tcc_new();
    tcc_set_options(s, "v");
    assert(s);

    tcc_set_output_type(s, TCC_OUTPUT_MEMORY);
    return s;
}

void compileCScript(TCCState* state, const std::string& script) {
    // add relevant library paths
    tcc_add_include_path(state, "include");
    tcc_add_library_path(state, "lib");
    tcc_add_library(state, "cpplib");

    // compile the source code and make it accessible (relocate)
    const bool compiled = tcc_compile_string(state, script.c_str()) >= 0;
    assert(compiled);

    void* program = calloc(1, tcc_relocate(state, NULL));
    assert(program);

    const bool relocated = tcc_relocate(state, program) >= 0;
    assert(relocated);
}

int main(int argc, char ** argv)
{
    assert(argc > 1);
    const std::string filePath = argv[1];

    const std::string& source = loadCScript(filePath);
    TCCState* s { createTCCState() };
    compileCScript(s, source);


    // obtain the TCC-compiled C function
    void* functionPointer = tcc_get_symbol(s, "tccCompiledCFunction");
    assert(functionPointer != nullptr);

    // bind it
    typedef const char* (*c_func_signature)();
    auto tccCompiledCFunction = reinterpret_cast<c_func_signature>(functionPointer);
    assert(tccCompiledCFunction);

    // call it
    std::cout << "Calling TCC-generated C function from main" << std::endl;
    const char* result = tccCompiledCFunction();
    std::cout << "Return value from tccCompiledCFunction is " << result << std::endl;


    // clean-up and signal success
    tcc_delete(s);
    return EXIT_SUCCESS;
}

