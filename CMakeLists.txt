cmake_minimum_required(VERSION 3.5)

project(AstroAlgo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libmeeus)
add_subdirectory(tools)

add_executable(ExampleTest main.cpp)

target_link_libraries(ExampleTest PUBLIC libmeeus)

# add the binary tree to the search path for include files
# so that we will find libmeeus.h
target_include_directories(ExampleTest PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/libmeeus"
                          )

enable_testing()

# does the application run
add_test(NAME Runs COMMAND ExampleTest )
