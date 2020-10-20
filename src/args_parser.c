/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 14:12:22 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/20 15:48:46 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define OPTIONS "-Ralrt"

/*
** Counting files and returning index of the first file
*/

static int	get_files_count(t_args *args)
{
	int i;

	i = args->opt_c;
	if ((i == 0 && args->argc > 1) || (args->argc - i >= i + 1 && i != 0))
	{
		++i;
	}
	args->files_c = args->argc - i;
	return (i);
}

/*
** Copying files to a new array
** args->files_c - files count
*/

char		**files_parser(t_args *args)
{
	char	**files;
	int		i;
	int		j;

	i = get_files_count(args);
	if (!(files = (char **)malloc(sizeof(char *) * (args->argc - i))))
		exit(EXIT_FAILURE);
	j = 0;
	if (ft_strcmp(args->argv[i], "--") == 0)
		if (++i == args->argc)
			files[j++] = ft_strdup(".");
	while (i < args->argc)
	{
		if (args->files_c == 1 && args->files_c + args->opt_c == args->argc)
			files[j] = ft_strdup(".");
		else
			files[j] = ft_strdup(args->argv[i]);
		++i;
		++j;
	}
	args->files_c = j;
	files = sort_args(args->files_c, files);
	return (files);
}

/*
** Option selection
*/

static void	get_options(char alpha, t_option *option)
{
	option->dot_files = (alpha == 'a') ? 1 : option->dot_files;
	option->time_sort = (alpha == 't') ? 1 : option->time_sort;
	option->long_format = (alpha == 'l') ? 1 : option->long_format;
	option->reverse_order = (alpha == 'r') ? 1 : option->reverse_order;
	option->recursive_read = (alpha == 'R') ? 1 : option->recursive_read;
}

/*
** Verification option
*/

static int	is_option(char *str, t_option *option)
{
	size_t	i;
	size_t	j;

	i = 1;
	if (str[i - 1] == '-' && str[i])
	{
		if (str[i] == '-' && !str[i + 1])
			return (1);
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
		return (0);
	}
	return (1);
}

/*
** Counting options
** ls_data->opt_c - options count
*/

void		options_parser(t_args *ls_data, t_option *option)
{
	int	i;

	option->dot_files = 0;
	option->time_sort = 0;
	option->long_format = 0;
	option->reverse_order = 0;
	option->recursive_read = 0;
	i = 1;
	while (i < ls_data->argc && !is_option(ls_data->argv[i], option))
	{
		++i;
	}
	--i;
	ls_data->opt_c = i;
}
