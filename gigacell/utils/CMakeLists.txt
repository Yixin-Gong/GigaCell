set(TARGET_NAME utils)

file(GLOB CPP_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")

set(INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/..)

add_library(${TARGET_NAME}_cxx STATIC ${CPP_SOURCES})
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")
target_include_directories(${TARGET_NAME}_cxx PUBLIC ${INCLUDE_DIRS})