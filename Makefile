# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/14 15:31:39 by fhelena           #+#    #+#              #
#    Updated: 2020/10/07 16:15:06 by fhelena          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= ft_ls
LIB				= libft.a
TARGET			= check.out

SRC_DIR			= src
TST_DIR			= tests
INC_DIR			= include
BLD_DIR			= build
LIB_DIR			= libft

-include		$(SRC_DIR)/src.mk
-include		$(TST_DIR)/test.mk

SRCS			= $(SRC)
TSTS			= $(TEST)
OBJS			= $(SRCS:%.c=$(BLD_DIR)/%.o)
DEPS			= $(SRCS:%.c=$(BLD_DIR)/%.d)
T_OBJS			= $(TSTS:%.c=$(BLD_DIR)/%.o)
T_DEPS			= $(TSTS:%.c=$(BLD_DIR)/%.d)

SHELL			= /bin/sh
CC				?= gcc
MKDIR			= mkdir -p
MAKE			= make -sC
RM				= rm -rf
NORME			= $(shell norminette $(SRCS) $(INC_DIR)\
				  | grep "Error" | wc -l | tr -d ' ')

CFLAGS			= -g -Wall -Wextra -Werror -Wpadded
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
	@printf "$(COLOR_G)PASS:$(C_RESET)\t$(NAME)\n"

PHONY			+= libft
libft:
	@$(MAKE) $(LIB_DIR)

PHONY			+= norme
norme:
ifeq ($(NORME), 0)
	@printf "$(COLOR_G)PASS:$(C_RESET)\tnorminette\t[$(NAME)]\n"
else
	@printf "$(COLOR_R)PASS:$(C_RESET)\tnorminette\t[$(NAME)] [$(NORME)]\n"
endif

PHONY			+= check
check:			norme all $(TARGET)
	@printf "$(COLOR_G)PASS:$(C_RESET)\t$(TARGET)\n"
	./$(TARGET)

$(NAME):		$(OBJS)
	@printf "\r$(R_CLEAN)Linking: $^ -> $@\n"
	@$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) -o $@ $^

$(TARGET):		$(T_OBJS)
	@printf "\r$(R_CLEAN)Linking: $^ -> $@\n"
	@$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) -o $@ $^

$(BLD_DIR)/%.o:	%.c $(LIB_DIR)/$(LIB)
	@$(MKDIR) $(dir $@)
	@printf "\r$(R_CLEAN)Assembling: $< -> $@"
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $< $(DFLAGS)

PHONY			+= clean
clean:
	@$(MAKE) $(LIB_DIR) clean
	@$(RM) $(OBJS)
	@printf "$(COLOR_G)PASS:$(C_RESET)\tmake clean\t[$(NAME)]\n"

PHONY			+= fclean
fclean:			clean
	@$(MAKE) $(LIB_DIR) fclean
	@$(RM) $(NAME) $(BLD_DIR)
	@printf "$(COLOR_G)PASS:$(C_RESET)\tmake fclean\t[$(NAME)]\n"

PHONY			+= re
re:				fclean all

-include $(wildcard $(DEPS))

.PHONY:			$(PHONY)
