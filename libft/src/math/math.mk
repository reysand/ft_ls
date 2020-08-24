# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    math.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/22 23:26:03 by fhelena           #+#    #+#              #
#    Updated: 2020/05/22 23:28:34 by fhelena          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MATH_DIR	= src/math/

MATH_SRCS	= ft_atoi.c \
			  ft_itoa.c \
			  ft_nbrlen.c

MATH	= $(addprefix $(MATH_DIR), $(MATH_SRCS))
