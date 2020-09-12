/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:44 by fhelena           #+#    #+#             */
/*   Updated: 2020/09/12 21:15:18 by fhelena          ###   ########.fr       */
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

	i = 1;
	init(&option);
	while (i < argc && !is_option(argv[i], &option))
		++i;
	if (argc - 1 == 0 || i - 1 == argc - 1)
		i -= 1;
	if (!(files = (char **)malloc(sizeof(char *) * (argc - i))))
		return (EXIT_FAILURE);
	j = 0;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "--") != 0 && argc != 1 && i != argc - 1)
			files[j] = ft_strdup(argv[i]);
		else
			files[j] = ft_strdup(".");
		++i;
		++j;
	}
	files = sort_args(j, files);
	i = 0;
	ret = EXIT_SUCCESS;
	while (i < j)
	{
		if (ft_ls(files[i], &option))
			ret = EXIT_FAILURE;
		++i;
	}
	return (ret);
}
