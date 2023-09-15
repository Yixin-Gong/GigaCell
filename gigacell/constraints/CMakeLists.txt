set(TARGET_NAME constraints)

file(GLOB CPP_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")

set(INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/..)

add_library(${TARGET_NAME}_cxx STATIC ${CPP_SOURCES})
target_include_directories(${TARGET_NAME}_cxx PUBLIC ${INCLUDE_DIRS})
