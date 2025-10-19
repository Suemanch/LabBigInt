#cmake_minimum_required(VERSION 3.30) # 3.0
#
#set(CMAKE_CXX_STANDARD 20)
#
#project(BigInt)
#
#set(exe_name ${PROJECT_NAME})
#
#add_subdirectory(googletest)
#
#add_library(corelib OBJECT BigInt.cpp)
#
#add_executable(${exe_name} main.cpp)
#
#target_link_libraries(${exe_name} PRIVATE corelib)
#
#target_link_libraries(gtest)



cmake_minimum_required(VERSION 3.30) # 3.0

set(CMAKE_CXX_STANDARD 20)

project(BigInt)

set(exe_name ${PROJECT_NAME})

add_subdirectory(googletest)

add_library(corelib OBJECT BigInt.cpp)

add_executable( ${PROJECT_NAME}
        main.cpp
#        BigInt.h
        BigInt.cpp
)

add_executable(tests
        tests/BigInt_test.cpp
        BigInt.cpp
)

#target_link_libraries(${exe_name} PRIVATE corelib)

target_link_libraries(tests gtest)