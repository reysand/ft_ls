# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    ft_printf.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/14 17:24:38 by fhelena           #+#    #+#              #
#    Updated: 2020/08/14 17:32:10 by fhelena          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FT_PRINTF_DIR	= src/io/ft_printf/

FT_PRINTF_SRCS	= ft_printf.c\
				  flags.c\
				  tools.c\
				  tools_width.c\
				  type_s.c\
				  type_p.c\
				  type_d.c\
				  type_o.c\
				  type_u.c\
				  type_x.c\
				  type_f.c

FT_PRINTF		= $(addprefix $(FT_PRINTF_DIR), $(FT_PRINTF_SRCS))
