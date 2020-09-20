/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:44 by fhelena           #+#    #+#             */
/*   Updated: 2020/09/19 17:20:45 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define OPTIONS	"-Ralrt"

/*
** Deallocating memory of matrix
*/

static void	ft_free(char **matrix, int size)
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
** Initializing the t_args and t_option structures
*/

static void	init(int argc, char **argv, t_args *args, t_option *option)
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
	t_args		args;
	t_option	option;
	char		**files;
	int			i;
	int			ret;

	init(argc, argv, &args, &option);
	options_parser(&args, &option);
	files = files_parser(&args);
	i = 0;
	ret = EXIT_SUCCESS;
	while (i < args.files_c)
	{
		if (ft_ls(files[i], &option))
		{
			ret = EXIT_FAILURE;
		}
		++i;
	}
	ft_free(files, args.files_c);
	ft_printf_fd(STDERR_FILENO, "\nOptions[%s]: %d %d %d %d %d\n", OPTIONS, \
			option.recursive_read, option.dot_files, option.long_format, \
			option.reverse_order, option.time_sort);
	exit(ret);
}
