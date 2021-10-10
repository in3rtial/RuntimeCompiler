#include "cpplib.h"
#include <iostream>


const char* externC_cppFunction() {
    std::cout << "Calling extern C C++ function from cpplib shared library" << std::endl;
    return "value returned from cpplib::externC_cppFunction";
}
