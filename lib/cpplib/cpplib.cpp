#include "cpplib.h"
#include <sstream>
#include <cstring>

const char* append_cpp_message(const char* msg)
{
    std::stringstream os;
    os << msg << std::endl;
    os << "C++ compiled code implements cpplib::append_cpp_message" << std::endl;
    const std::string tmp = os.str();
    char* result = new char[tmp.size()];
    strcpy(result, tmp.c_str());
    return result;
}
