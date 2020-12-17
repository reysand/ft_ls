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
			  free.c

SRC			= $(addprefix $(SRC_DIR), $(SRC_SRCS))
