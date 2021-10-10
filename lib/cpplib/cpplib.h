#ifndef CPPLIB_H
#define CPPLIB_H

// https://isocpp.org/wiki/faq/mixing-c-and-cpp#cpp-objs-passed-to-c
#ifdef __cplusplus
extern "C"
#endif
const char* externC_cppFunction();

#endif /* CPPLIB_H */
