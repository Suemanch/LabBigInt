cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 20)

project(BigInt)

set(exe_name ${PROJECT_NAME})

#if (MSVC)
#    # warning level 4 and all warnings as errors
#    add_compile_options(/W4 /WX)
#endif()

add_library(corelib OBJECT classBigInt.cpp)

add_executable(${exe_name} main.cpp)
target_link_libraries(${exe_name} PRIVATE corelib)