# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mem.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/22 23:28:46 by fhelena           #+#    #+#              #
#    Updated: 2020/05/22 23:33:03 by fhelena          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MEM_DIR		= src/mem/

MEM_SRCS	= ft_bzero.c \
			  ft_memalloc.c \
			  ft_memccpy.c \
			  ft_memchr.c \
			  ft_memcmp.c \
			  ft_memcpy.c \
			  ft_memdel.c \
			  ft_memmove.c \
			  ft_memset.c \
			  ft_realloc.c

MEM	 = $(addprefix $(MEM_DIR), $(MEM_SRCS))
