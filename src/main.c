/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:44 by fhelena           #+#    #+#             */
/*   Updated: 2020/09/13 20:25:09 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define OPTIONS	"-Ralrt"

static char	**sort_args(int argc, char **argv)
{
	int		i;
	int		is_sorted;
	char	*tmp;

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
			i = 1;
			is_sorted = 0;
		}
	}
	return (argv);
}

static void	parse_options(char alpha, t_option *option)
{
	option->recursive_read = (alpha == 'R') ? 1 : option->recursive_read;
	option->dot_files = (alpha == 'a') ? 1 : option->dot_files;
	option->long_format = (alpha == 'l') ? 1 : option->long_format;
	option->reverse_order = (alpha == 'r') ? 1 : option->reverse_order;
	option->time_sort = (alpha == 't') ? 1 : option->time_sort;
}

static int	is_option(char *str, t_option *option)
{
	size_t	i;
	size_t	j;

	i = 1;
	if (str[i - 1] == '-' && str[i])
	{
		if (str[i] == '-' && !str[i + 1])
			return (EXIT_FAILURE);
		while (str[i])
		{
			j = 1;
			while (OPTIONS[j] != str[i] && j < ft_strlen(OPTIONS))
				++j;
			if (str[i] != OPTIONS[j])
			{
				ft_printf("ft_ls: illegal option -- %c\n", str[i]);
				ft_printf("usage: ft_ls [%s] [file ...]\n", OPTIONS);
				exit(EXIT_FAILURE);
			}
			parse_options(str[i], option);
			++i;
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/*
** Initialization of options
*/

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
	t_option	option;
	char		**files;
	int			i;
	int			j;
	int			ret;
	int			options_count;

	i = 1;
	init(&option);
	// Count and parse options
	while (i < argc && !is_option(argv[i], &option))
	{
		++i;
	}
	options_count = i - 1;
	ft_printf_fd(STDERR_FILENO, "options_count: %d\n", options_count);
	ft_printf_fd(STDERR_FILENO, "argc: %d;\ti: %d ", argc, i);
	if (argc - 1 == 0 || i - 1 == argc - 1)
	{
		i -= 1;
	}
	ft_printf_fd(STDERR_FILENO, "=> %d\n", i);
	ft_printf_fd(STDERR_FILENO, "files_count: %d\n", argc - i);
	// Allocate memory for array of files
	if (!(files = (char **)malloc(sizeof(char *) * (argc - i))))
	{
		exit(EXIT_FAILURE);
	}
	j = 0;
	// Add files to new array
	ret = options_count + argc - i;
	while (i < argc)
	{
		ft_printf_fd(STDERR_FILENO, "%s ", argv[i]);
		if (ft_strcmp(argv[i], "--") != 0 && argc != 1 && ret != argc)
		{
			files[j] = ft_strdup(argv[i]);
		}
		else
		{
			files[j] = ft_strdup(".");
		}
		ft_printf_fd(STDERR_FILENO, "-> %s\n", files[j]);
		++i;
		++j;
	}
	// Sort files
	files = sort_args(j, files);
	i = 0;
	ret = EXIT_SUCCESS;
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
