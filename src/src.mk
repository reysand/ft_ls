SRC_DIR		= src/

SRC_SRCS	= main.c\
			  args_parser.c\
			  ft_ls.c\
			  lists.c\
			  sorting.c\
			  output.c\
			  free.c

SRC			= $(addprefix $(SRC_DIR), $(SRC_SRCS))
