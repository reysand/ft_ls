# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    io.mk                                              :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/22 22:56:45 by fhelena           #+#    #+#              #
#    Updated: 2020/08/14 17:30:40 by fhelena          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

IO_DIR	= src/io/

IO_SRCS	= ft_putchar.c \
		  ft_putchar_fd.c \
		  ft_putendl.c \
		  ft_putendl_fd.c \
		  ft_putnbr.c \
		  ft_putnbr_fd.c \
		  ft_putstr.c \
		  ft_putstr_fd.c \
		  get_next_line.c

-include src/io/ft_printf/ft_printf.mk

IO	= $(addprefix $(IO_DIR), $(IO_SRCS)) $(FT_PRINTF)
