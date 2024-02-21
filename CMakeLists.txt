cmake_minimum_required(VERSION 3.0)
project(Aguzarov_R_BigInt)
find_package(GTest)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(BigInt)
add_subdirectory(googletest)
include(GoogleTest)
add_executable(tests
        all_tests/divide_tests.cpp
        all_tests/mult_tests.cpp
        all_tests/plus_tests.cpp
        all_tests/sub_tests.cpp
        all_tests/comp.cpp)
enable_testing()
add_executable(main main.cpp)
target_link_libraries(main BigInt)
target_link_libraries(tests BigInt gtest gtest_main)