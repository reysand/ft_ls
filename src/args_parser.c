/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 14:12:22 by fhelena           #+#    #+#             */
/*   Updated: 2020/09/17 20:13:34 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define OPTIONS "-Ralrt"

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
			i = 1;
			is_sorted = 0;
		}
	}
	return (argv);
}

static void	get_options(char alpha, t_option *option)
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
			get_options(str[i++], option);
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int			options_parser(t_args *args, t_option *option)
{
	int	i;

	i = 1;
	while (i < args->argc && !is_option(args->argv[i], option))
	{
		++i;
	}
	args->option_count = --i;
	ft_printf_fd(STDERR_FILENO, "options_count: %d\n", i);
	return (i);
}

char		**files_parser(t_args *args)
{
	char	**files;
	int		i;
	int		j;
	int		k;

	i = args->option_count;
	if (i && (args->argc - 1 == 0 || i - 1 == args->argc - 1))
		i -= 1;
	if (args->argc - i > 1)
		++i;
	ft_printf_fd(STDERR_FILENO, "files_count: %d\n", args->argc - i);
	if (!(files = (char **)malloc(sizeof(char *) * (args->argc - i))))
		exit(EXIT_FAILURE);
	j = 0;
	k = args->option_count + args->argc - i;
	ft_printf("%d %d %d\n", k, i, args->argc);
	while (i < args->argc)
	{
		ft_printf_fd(STDERR_FILENO, "%s ", args->argv[i]);
		if (ft_strcmp(args->argv[i], "--") != 0 && args->argc != 1 && k != args->argc)
			files[j] = ft_strdup(args->argv[i]);
		else
			files[j] = ft_strdup(".");
		ft_printf_fd(STDERR_FILENO, "-> %s\n", files[j]);
		++i;
		++j;
	}
	files = sort_args(j, files);
	return (files);
}
