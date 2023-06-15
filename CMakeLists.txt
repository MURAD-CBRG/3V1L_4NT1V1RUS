cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)

project(antivirus_proj)

add_subdirectory(sqllite)
add_subdirectory(sha256)

add_executable(antivirus antivirus.cpp)
add_executable(test signature.cpp)

target_link_libraries(test sqllib)
target_link_libraries(antivirus sqllib)
target_link_libraries(antivirus shalib)
set_target_properties(antivirus PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY output
)
