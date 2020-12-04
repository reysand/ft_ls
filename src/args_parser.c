/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 14:12:22 by fhelena           #+#    #+#             */
/*   Updated: 2020/12/03 03:05:42 by reysand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	get_file_position(t_args *ls)
{
	int i;

	i = ls->opt_c;
	if ((i == 0 && ls->argc > 1) || (ls->argc - i >= i + 1 && i != 0))
	{
		++i;
	}
	ls->files_c = ls->argc - i;
	return (i);
}

char		**files_parser(t_args *ls)
{
	char	**files;
	int		i;
	int		j;

	ls->files = NULL;
	i = get_file_position(ls);
	if (!(files = (char **)malloc(sizeof(char *) * (ls->files_c))))
		exit(EXIT_FAILURE);
	j = 0;
	if (ft_strcmp(ls->argv[i], "--") == 0)
		if (++i == ls->argc)
			files[j++] = ft_strdup(".");
	while (i < ls->argc)
	{
		if (ls->files_c == 1 && ls->files_c + ls->opt_c == ls->argc)
			files[j] = ft_strdup(".");
		else
			files[j] = ft_strdup(ls->argv[i]);
		++i;
		++j;
	}
	ls->files_c = j;
	files = get_ascii_sorted_args(ls->files_c, files);
	return (files);
}

static void	get_options(char alpha, t_opts *option)
{
	option->size = (alpha == 's') ? 1 : option->size;
	option->dot_files = (alpha == 'a') ? 1 : option->dot_files;
	option->time_sort = (alpha == 't') ? 1 : option->time_sort;
	option->long_format = (alpha == 'l') ? 1 : option->long_format;
	option->reverse_sort = (alpha == 'r') ? 1 : option->reverse_sort;
	option->recursive_read = (alpha == 'R') ? 1 : option->recursive_read;
}

static int	is_option(char *str, t_opts *option)
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

void		options_parser(t_args *ls, t_opts *option)
{
	int	i;

	option->dot_files = 0;
	option->time_sort = 0;
	option->long_format = 0;
	option->reverse_sort = 0;
	option->recursive_read = 0;
	i = 1;
	while (i < ls->argc && !is_option(ls->argv[i], option))
	{
		++i;
	}
	ls->opt_c = i - 1;
}
