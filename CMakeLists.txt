cmake_minimum_required(VERSION 3.22)
project(Aguzarov_R_BigInt)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(BigInt)
add_executable(main main.cpp)
target_link_libraries(main BigInt)
