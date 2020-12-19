cmake_minimum_required(VERSION 3.16.3)
project(ft_ls VERSION 0.2.0 LANGUAGES C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")

add_subdirectory(libft)

set(HEADERS
        include/ft_ls.h include/ft_ls_structs.h)
set(SOURCES
        src/args_parser.c src/free.c src/ft_ls.c src/lists.c src/long_format.c src/main.c src/output.c src/sorting.c
		src/long_format_2.c src/utils.c src/long_format_3.c)

add_executable(ft_ls ${SOURCES} ${HEADERS})
target_include_directories(ft_ls PRIVATE include libft/include)
target_link_libraries(ft_ls ft)