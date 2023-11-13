set(TARGET_NAME database)

file(GLOB CPP_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cc")

set(INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)

set(LINK_LIBS
        utils_cxx
        -static-libgcc
        -static-libstdc++
)

add_library(${TARGET_NAME}_cxx STATIC ${CPP_SOURCES})
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")
target_include_directories(${TARGET_NAME}_cxx PUBLIC ${INCLUDE_DIRS})
target_link_directories(${TARGET_NAME}_cxx PUBLIC ${LINK_LIBS})
