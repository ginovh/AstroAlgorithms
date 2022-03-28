add_executable(ExampleTest1 main.cpp)

target_link_libraries(ExampleTest1 PUBLIC libmeeus)

target_include_directories(ExampleTest1 PUBLIC
                          "${PROJECT_SOURCE_DIR}/libmeeus"
                          )
