# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/21 23:28:59 by fhelena           #+#    #+#              #
#    Updated: 2020/09/08 16:08:55 by fhelena          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= libft.a

SRC_DIR			= src
INC_DIR			= include
BLD_DIR			= build

-include src/char/char.mk
-include src/io/io.mk
-include src/lst/lst.mk
-include src/math/math.mk
-include src/mem/mem.mk
-include src/str/str.mk

SRCS			= $(CHAR) $(IO) $(LST) $(MATH) $(MEM) $(STR)
OBJS			= $(SRCS:%.c=$(BLD_DIR)/%.o)
DEPS			= $(SRCS:%.c=$(BLD_DIR)/%.d)

SHELL			= /bin/sh
CC				?= gcc
AR				= ar
RM				= rm -rf
MKDIR			= mkdir -p
NORME			= $(shell norminette $(SRCS) $(INC_DIR)\
				  | grep "Error" | wc -l | tr -d ' ')

AFLAGS			= -rsuv
CFLAGS			= -Wall -Wextra -Werror
DFLAGS			= -MMD
IFLAGS			= -I $(INC_DIR)

R_CLEAN			= \033[K
C_RESET			= \033[00m
COLOR_R			= \033[31m
COLOR_G			= \033[32m

PHONY			+= all
all:			$(NAME)
	@printf "\r$(COLOR_G)PASS:$(C_RESET)\tlibft\n"

PHONY			+= norme
norme:
ifeq ($(NORME), 0)
	@printf "$(COLOR_G)PASS:$(C_RESET)\tnorminette\t[libft]\n"
else
	@printf "$(COLOR_R)FAIL:$(C_RESET)\tnorminette\t[libft] [$(NORME)]\n"
endif

PHONY			+= check
check:			norme all

$(NAME):		$(OBJS)
	@printf "\r$(R_CLEAN)"
	@$(AR) $(ARFLAGS) $@ $?

$(BLD_DIR)/%.o:	%.c
	@$(MKDIR) $(dir $@)
	@printf "\r$(R_CLEAN)Assembling: $< -> $@"
	@$(CC) $(CFLAGS) $(DFLAGS) $(IFLAGS) -o $@ -c $<

PHONY			+= clean
clean:
	@$(RM) $(OBJS)
	@printf "$(COLOR_G)PASS:$(C_RESET)\tmake clean\t[libft]\n"

PHONY			+= fclean
fclean:			clean
	@$(RM) $(NAME) $(BLD_DIR)
	@printf "$(COLOR_G)PASS:$(C_RESET)\tmake fclean\t[libft]\n"

PHONY			+= re
re:				fclean all

-include $(wildcard $(DEPS))

.PHONY:			$(PHONY)
