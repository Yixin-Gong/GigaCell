set(TARGET_NAME partition)

file(GLOB CPP_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")

set(INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/..)

set(LINK_LIBS
        placement_cxx)

add_library(${TARGET_NAME}_cxx STATIC ${CPP_SOURCES})
target_include_directories(${TARGET_NAME}_cxx PUBLIC ${INCLUDE_DIRS})
target_link_directories(${TARGET_NAME}_cxx PUBLIC ${LINK_LIBS})