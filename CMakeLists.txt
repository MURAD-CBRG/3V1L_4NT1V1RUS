cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Debug)

project(test_proj)

include_directories(sha256)
link_directories(sha256)
add_subdirectory(sha256)

include_directories(sqllite)
link_directories(sqllite)
add_subdirectory(sqllite)

add_executable(testfile test.cpp conf.cpp bypass.cpp signature.cpp database_api.cpp)
target_link_libraries(testfile shalib sqlib) 

enable_testing()
