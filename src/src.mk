SRC_DIR		= src/

SRC_SRCS	= main.c\
			  args_parser.c\
			  ft_ls.c\
			  options.c\
			  output.c

SRC			= $(addprefix $(SRC_DIR), $(SRC_SRCS))
