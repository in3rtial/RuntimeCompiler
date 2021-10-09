#ifndef CPPLIB_H
#define CPPLIB_H

// https://isocpp.org/wiki/faq/mixing-c-and-cpp#cpp-objs-passed-to-c
#ifdef __cplusplus
extern "C"
#endif
const char* append_cpp_message(const char* msg);

#endif /* CPPLIB_H */
