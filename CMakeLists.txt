cmake_minimum_required(VERSION 3.17)
project(ft_ls VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_BUILD_PARALLEL_LEVEL 1)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -Wpadded")

add_subdirectory(libft)

set(HEADERS
        include/ft_ls.h)
set(SOURCES
        src/main.c src/args_parser.c src/ft_ls.c src/sorting.c src/output.c
        src/free.c)
add_executable(ft_ls ${SOURCES} ${HEADERS})
target_include_directories(ft_ls PRIVATE include libft/include)
target_link_libraries(ft_ls ft)

add_custom_target(makefile
        COMMAND make -j 1
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
