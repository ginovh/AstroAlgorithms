cmake_minimum_required(VERSION 3.5)

project(JulianDate LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libmeeus)

add_executable(JulianDate main.cpp)

target_link_libraries(JulianDate PUBLIC libmeeus)

# add the binary tree to the search path for include files
# so that we will find libmeeus.h
target_include_directories(JulianDate PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/libmeeus"
                          )

enable_testing()

# does the application run
add_test(NAME Runs COMMAND JulianDate )
