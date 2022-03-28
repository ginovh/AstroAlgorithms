add_executable(Generate_VSOP87_code Generate_vsop87_code.cpp)

target_link_libraries(Generate_VSOP87_code PUBLIC libmeeus)

target_include_directories(Generate_VSOP87_code PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/libmeeus"
                          )
