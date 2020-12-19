cmake_minimum_required(VERSION 3.16.3)
project(libft VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")

set(HEADERS
		include/ft_list.h include/ft_printf.h include/get_next_line.h include/libft.h include/ft_printf_structs.h)
set(SOURCES
		src/char/ft_isalnum.c src/char/ft_isalpha.c src/char/ft_isascii.c src/char/ft_isdigit.c src/char/ft_isprint.c
		src/char/ft_tolower.c src/char/ft_toupper.c src/io/ft_putchar.c src/io/ft_putchar_fd.c src/io/ft_putendl.c
		src/io/ft_putendl_fd.c src/io/ft_putnbr.c src/io/ft_putnbr_fd.c src/io/ft_putstr.c src/io/ft_putstr_fd.c
		src/io/get_next_line.c src/io/ft_printf/ft_printf.c src/io/ft_printf/flags.c src/io/ft_printf/tools.c
		src/io/ft_printf/tools_width.c src/io/ft_printf/type_s.c src/io/ft_printf/type_p.c src/io/ft_printf/type_d.c
		src/io/ft_printf/type_o.c src/io/ft_printf/type_u.c src/io/ft_printf/type_x.c src/io/ft_printf/type_f.c
		src/lst/ft_lstadd.c src/lst/ft_lstdel.c src/lst/ft_lstdelone.c src/lst/ft_lstiter.c src/lst/ft_lstmap.c
		src/lst/ft_lstnew.c src/lst/ft_lstrev.c src/math/ft_atoi.c src/math/ft_itoa.c src/math/ft_nbrlen.c
		src/mem/ft_bzero.c src/mem/ft_memalloc.c src/mem/ft_memccpy.c src/mem/ft_memchr.c src/mem/ft_memcmp.c
		src/mem/ft_memcpy.c src/mem/ft_memdel.c src/mem/ft_memmove.c src/mem/ft_memset.c src/mem/ft_realloc.c
		src/str/ft_strcat.c src/str/ft_strchr.c src/str/ft_strclr.c src/str/ft_strcmp.c src/str/ft_strcpy.c
		src/str/ft_strdel.c src/str/ft_strdup.c src/str/ft_strequ.c src/str/ft_striter.c src/str/ft_striteri.c
		src/str/ft_strjoin.c src/str/ft_strlcat.c src/str/ft_strlcpy.c src/str/ft_strlen.c src/str/ft_strmap.c
		src/str/ft_strmapi.c src/str/ft_strncat.c src/str/ft_strncmp.c src/str/ft_strncpy.c src/str/ft_strnequ.c
		src/str/ft_strnew.c src/str/ft_strnstr.c src/str/ft_strrchr.c src/str/ft_strsplit.c src/str/ft_strstr.c
		src/str/ft_strsub.c src/str/ft_strtrim.c src/str/ft_wordcount.c)

add_library(ft ${SOURCES} ${HEADERS})
target_include_directories(ft PRIVATE include)