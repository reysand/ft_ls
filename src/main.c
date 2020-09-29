/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:44 by fhelena           #+#    #+#             */
/*   Updated: 2020/09/28 14:12:54 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define OPTIONS	"-Ralrt"

/*
** Deallocating memory of matrix
*/

static void	free_matrix(char **matrix, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(matrix[i]);
		++i;
	}
	free(matrix);
}

/*
** File and option handling with creating list of files
*/

int			args_handler(char **files, t_args *args, t_option *option)
{
	t_file	*file_info;
	int		i;
	int		ret;

	i = 0;
	ret = EXIT_SUCCESS;
	file_info = NULL;
	while (i < args->files_c)
	{
		if (ft_ls(files[i], &file_info, option, i, ret))
			ret = EXIT_FAILURE;
		/*
		** Needed add to list of file_info
		*/
		/*
		if (file_info)
		{
			if (i >= 0)
			{
				if (ret == EXIT_SUCCESS && i > 0 && i < args->files_c)
					ft_printf("\n");
				ft_printf("%s:\n", files[i]);
			}
			get_ascii_sort(&file_info);
			print_list(file_info);
			*/free_list(file_info);/*
			file_info = NULL;
		}
		*/
		++i;
	}
	free_matrix(files, args->files_c);
	ft_printf_fd(STDERR_FILENO, "\nOptions[%s]: %d %d %d %d %d\n", OPTIONS, \
			option->recursive_read, option->dot_files, option->long_format, \
			option->reverse_order, option->time_sort);
	return (ret);
}

/*
** Sorting arguments
*/

static char	**sort_args(int argc, char **argv)
{
	char	*tmp;
	int		i;
	int		is_sorted;

	i = 0;
	is_sorted = 0;
	while (i < argc - 1)
	{
		if (ft_strcmp(argv[i], argv[i + 1]) > 0)
		{
			tmp = argv[i];
			argv[i] = argv[i + 1];
			argv[i + 1] = tmp;
			is_sorted = 1;
		}
		++i;
		if (i == argc - 1 && is_sorted)
		{
			i = 0;
			is_sorted = 0;
		}
	}
	return (argv);
}

/*
** Initializing the t_args and t_option structures
*/

static void	structs_init(int argc, char **argv, t_args *args, t_option *option)
{
	args->argc = argc;
	args->argv = argv;
	option->dot_files = 0;
	option->time_sort = 0;
	option->long_format = 0;
	option->reverse_order = 0;
	option->recursive_read = 0;
}

int			main(int argc, char **argv)
{
	t_args		ls_args;
	t_option	options;
	char		**files;

	structs_init(argc, argv, &ls_args, &options);
	options_parser(&ls_args, &options);
	files = files_parser(&ls_args);
	files = sort_args(ls_args.files_c, files);
	exit(args_handler(files, &ls_args, &options));
}
