file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/libmeeus/vsop87d/*.cpp)

add_library(libmeeus libmeeus.cpp ${SRC_FILES})

target_include_directories(libmeeus PUBLIC
                          "${PROJECT_SOURCE_DIR}/libmeeus"
                          )
