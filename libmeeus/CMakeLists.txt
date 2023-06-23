file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/libmeeus/vsop87d/*.cpp)
set(HEADER_FILES ${PROJECT_SOURCE_DIR}/libmeeus/vsop87d/VSOP87D.h)

add_library(libmeeus libmeeus.cpp libmeeus.h ${SRC_FILES} ${HEADER_FILES})

target_include_directories(libmeeus PUBLIC
                          "${PROJECT_SOURCE_DIR}/libmeeus"
                          )
