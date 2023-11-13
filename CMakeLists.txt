cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(GigaCell LANGUAGES CXX)
add_compile_options(-Ofast)
set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "verbose makefile output")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY POSITION_INDEPENDENT_CODE TRUE)

add_subdirectory(gigacell)
