set(TARGET_NAME main)

file(GLOB CPP_SOURCES
        gigaplace.h
        gigaplace.cc)

file(GLOB BIN_SOURCES
        main.h
        main.cc)


set(INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/..)

set(LINK_LIBS
        placement_cxx
        utils_cxx
        parser_cxx
#        writer_cxx
)
include_directories(utils)
add_executable(GigaPlace ${BIN_SOURCES} ${CPP_SOURCES})
target_include_directories(GigaPlace PUBLIC ${INCLUDE_DIRS})
target_link_directories(GigaPlace PUBLIC ${LINK_LIBS})
target_link_libraries(GigaPlace PUBLIC ${LINK_LIBS})