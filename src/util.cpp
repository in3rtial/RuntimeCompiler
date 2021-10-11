#include "util.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <libtcc.h>

namespace util {

std::string readFile(const std::string& file) {
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

void compileCScript(TCCState* state, const std::string& script,
                    const std::vector<std::string>& includePaths,
                    const std::vector<std::string>& libraryPaths,
                    const std::vector<std::string>& libraries) {
    // setup environment
    for(const std::string& includePath : includePaths) {
        tcc_add_include_path(state, includePath.c_str());
    }
    for(const std::string& libraryPath : libraryPaths) {
        tcc_add_library_path(state, libraryPath.c_str());
    }
    for(const std::string& library : libraries) {
        tcc_add_library(state, library.c_str());
    }

    // compile the source code and make it accessible (relocate)
    const bool compiled = tcc_compile_string(state, script.c_str()) >= 0;
    assert(compiled);

    void* program = calloc(1, tcc_relocate(state, NULL));
    assert(program);

    const bool relocated = tcc_relocate(state, program) >= 0;
    assert(relocated);
}

}
