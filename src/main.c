/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:44 by fhelena           #+#    #+#             */
/*   Updated: 2020/09/15 19:35:37 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define OPTIONS	"-Ralrt"

static void	init(t_option *option)
{
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
	int			j;
	int			ret;

	args.argc = argc;
	args.argv = argv;
	init(&option);
	options_parser(&args, &option);
	files = files_parser(&args);
	ret = EXIT_SUCCESS;
	j = args.option_count;
	if (j && (args.argc - 1 == 0 || j - 1 == args.argc - 1))
		j -= 1;
	i = 0;
	j = args.argc - j;
	while (i < j)
	{
		ft_printf_fd(STDERR_FILENO, "file [%d]: %s\n", i, files[i]);
		if (ft_ls(files[i], &option))
		{
			ret = EXIT_FAILURE;
		}
		ft_printf_fd(STDERR_FILENO, "file [%d]: ret = %d\n", i, ret);
		++i;
	}
	i = 0;
	while (i < j)
	{
		free(files[i]);
		++i;
	}
	free(files);
	ft_printf_fd(STDERR_FILENO, "\nOptions[%s]: %d %d %d %d %d\n", OPTIONS, \
			option.recursive_read, option.dot_files, option.long_format, \
			option.reverse_order, option.time_sort);
	ft_printf_fd(STDERR_FILENO, "Return: %d\n", ret);
	exit(ret);
}
