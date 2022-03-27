cmake_minimum_required(VERSION 3.5)

project(AstroAlgo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libmeeus)
add_subdirectory(tools)
add_subdirectory(tests)

enable_testing()

# does the application run
add_test(NAME Runs COMMAND ExampleTest1 )
add_test(NAME Generate1 COMMAND Generate_VSOP87_headers )
