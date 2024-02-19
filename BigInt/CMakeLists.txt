file(GLOB_RECURSE SOURCES "*.cpp")
add_library(BigInt SHARED ${SOURCES})
target_include_directories(BigInt PUBLIC BigInt.h)