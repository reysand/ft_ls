# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    lst.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/22 23:03:26 by fhelena           #+#    #+#              #
#    Updated: 2020/05/22 23:33:19 by fhelena          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LST_DIR		= src/lst/

LST_SRCS	= ft_lstadd.c \
			  ft_lstdel.c \
			  ft_lstdelone.c \
			  ft_lstiter.c \
			  ft_lstmap.c \
			  ft_lstnew.c \
			  ft_lstrev.c

LST = $(addprefix $(LST_DIR), $(LST_SRCS))
