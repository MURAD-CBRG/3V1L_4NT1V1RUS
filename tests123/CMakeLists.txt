cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project(antivirus_proj)

add_executable(testfile test.cpp conf.cpp bypass.cpp)

enable_testing()
