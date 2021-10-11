#include "util.h"
#include <iostream>
#include <cassert>
#include <libtcc.h>

int main(int argc, char ** argv)
{
    assert(argc > 1);
    const std::string filePath = argv[1];

    const std::string& source = util::readFile(filePath);
    TCCState* s = util::createTCCState();
    util::compileCScript(s, source, {"include"}, {"lib"}, {"cpplib"});

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

