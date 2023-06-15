cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)

project(antivirus_proj)

add_library(sha256 sha256/sha256.cpp sha256/sha256.h)

add_executable(antivirus antivirus.cpp)

target_link_libraries(antivirus sha256)
set_target_properties(antivirus PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY output
)