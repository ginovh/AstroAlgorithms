add_executable(ExampleTest1 main.cpp)

target_link_libraries(ExampleTest1 PUBLIC libmeeus)

# add the binary tree to the search path for include files
# so that we will find libmeeus.h
target_include_directories(ExampleTest1 PUBLIC
                          "${PROJECT_SOURCE_DIR}/libmeeus"
                          "${PROJECT_SOURCE_DIR}/vsop87d"
                          )
