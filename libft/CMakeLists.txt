cmake_minimum_required(VERSION 3.17)
project(libft VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")

file (GLOB_RECURSE SOURCES src src/*.c)
file(GLOB_RECURSE HEADERS include include/*.h)

add_library(ft ${SOURCES} ${HEADERS})
target_include_directories(ft PRIVATE include)
