cmake_minimum_required(VERSION 3.16)

project(test)

add_subdirectory(
    wait/
)


set(CMAKE_VERBOSE_MAKEFILE 1)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O0")
add_compile_options(-Wall -Wextra -pedantic)