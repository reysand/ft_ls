# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/14 15:31:39 by fhelena           #+#    #+#              #
#    Updated: 2020/08/25 18:58:55 by fhelena          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= ft_ls

SRC_DIR			= src
INC_DIR			= include
BLD_DIR			= build
LIB_DIR			= libft

-include src/src.mk

SRCS			= $(SRC)
OBJS			= $(SRCS:%.c=$(BLD_DIR)/%.o)
DEPS			= $(SRCS:%.c=$(BLD_DIR)/%.d)

SHELL			= /bin/sh
CC				?= gcc
MKDIR			= mkdir -p
MAKE			= make -sC
RM				= rm -rf
NORME			= $(shell norminette $(SRCS) $(INC_DIR)\
				  | grep "Error" | wc -l | tr -d ' ')

CFLAGS			= -Wall -Wextra -Werror -g
DFLAGS			= -MT $@ -MMD -MP
IFLAGS			= -I $(INC_DIR) -I $(LIB_DIR)/$(INC_DIR)
LFLAGS			= -L $(LIB_DIR) -lft

R_CLEAN			= \033[K
C_RESET			= \033[00m
COLOR_R			= \033[31m
COLOR_G			= \033[32m
COLOR_Y			= \033[33m

PHONY			+= all
all:			libft $(NAME)
	@printf "$(COLOR_G)PASS:$(C_RESET)\tft_ls\n"

debug:
	@echo "$(OBJS)"

PHONY			+= libft
libft:
	@$(MAKE) $(LIB_DIR)

PHONY			+= norme
norme:
ifeq ($(NORME), 0)
	@printf "$(COLOR_G)PASS:$(C_RESET)\tnorminette\t[ft_ls]\n"
else
	@printf "$(COLOR_R)PASS:$(C_RESET)\tnorminette\t[ft_ls] [$(NORME)]\n"
endif

PHONY			+= check
check:			norme all
	./$(NAME)

$(NAME):		$(OBJS)
	@printf "\r$(R_CLEAN)Linking: $^ -> $@\n"
	@$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) -o $@ $^

$(BLD_DIR)/%.o:	%.c
	@$(MKDIR) $(dir $@)
	@printf "\r$(R_CLEAN)Assembling: $< -> $@"
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $< $(DFLAGS)

PHONY			+= clean
clean:
	@$(MAKE) $(LIB_DIR) clean
	@$(RM) $(OBJS)
	@printf "$(COLOR_G)PASS:$(C_RESET)\tmake clean\t[ft_ls]\n"

PHONY			+= fclean
fclean:
	@$(MAKE) $(LIB_DIR) fclean
	@$(RM) $(NAME) $(BLD_DIR)
	@printf "$(COLOR_G)PASS:$(C_RESET)\tmake fclean\t[ft_ls]\n"

PHONY			+= re
re:				fclean all

-include $(wildcard $(DEPS))

.PHONY:			$(PHONY)
