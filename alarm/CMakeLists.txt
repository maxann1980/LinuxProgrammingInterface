cmake_minimum_required(VERSION 3.16)

project(alarm)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/alarm.c
)


set(CMAKE_VERBOSE_MAKEFILE 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CFLAGS} -Wall -Wextra -pedantic -pthread")
add_compile_options(-Wall -Wextra -pedantic -pthread)