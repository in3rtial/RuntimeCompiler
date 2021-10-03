cmake_minimum_required(VERSION 3.14)
project(ApprovalTests)

set(CMAKE_CXX_STANDARD 17)

include_directories(include/tcc-0.9.27)
link_directories(include/tcc-0.9.27)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)


add_executable(tinyccdemo src/tinyccdemo.cpp)
#target_link_libraries(tinyccdemo gtest_main libtcc.a dl)

#gtest_discover_tests(tinyccdemo)
target_link_libraries(tinyccdemo libtcc.a libtcc1.a dl)

