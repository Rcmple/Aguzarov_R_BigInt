cmake_minimum_required(VERSION 3.0)
project(Aguzarov_R_BigInt)
find_package(GTest)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(BigInt)
add_subdirectory(googletest)
include(GoogleTest)
add_executable(tests
        divide_tests.cpp
        mult_tests.cpp
        plus_tests.cpp
        sub_tests.cpp)
enable_testing()
add_executable(main main.cpp)
target_link_libraries(main BigInt)
target_link_libraries(tests BigInt gtest gtest_main)