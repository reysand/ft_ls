# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    char.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/22 22:37:41 by fhelena           #+#    #+#              #
#    Updated: 2020/05/22 23:22:12 by fhelena          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CHAR_DIR	= src/char/

CHAR_SRCS	= ft_isalnum.c \
			  ft_isalpha.c \
			  ft_isascii.c \
			  ft_isdigit.c \
			  ft_isprint.c \
			  ft_tolower.c \
			  ft_toupper.c

CHAR	= $(addprefix $(CHAR_DIR), $(CHAR_SRCS))
