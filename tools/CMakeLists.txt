add_executable(Generate_VSOP87_headers Generate_vsop87_headers.cpp)

target_link_libraries(Generate_VSOP87_headers PUBLIC libmeeus)

# add the binary tree to the search path for include files
# so that we will find libmeeus.h
target_include_directories(Generate_VSOP87_headers PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/libmeeus"
                          )
