add_library(cpplib SHARED cpplib.cpp)

install(TARGETS cpplib DESTINATION ${CMAKE_BINARY_DIR}/lib)
install(FILES cpplib.h DESTINATION ${CMAKE_BINARY_DIR}/include)
