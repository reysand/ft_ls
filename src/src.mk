# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/24 17:54:56 by fhelena           #+#    #+#              #
#    Updated: 2020/12/24 19:27:20 by fhelena          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		= src/

SRC_SRCS	= main.c\
			  args_parser.c\
			  utils.c\
			  ft_ls.c\
			  lists.c\
			  sorting.c\
			  output.c\
			  long_format.c\
			  long_format_2.c\
			  long_format_3.c\
			  free.c

SRC			= $(addprefix $(SRC_DIR), $(SRC_SRCS))
