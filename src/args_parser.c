/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 14:12:22 by fhelena           #+#    #+#             */
/*   Updated: 2020/12/22 17:11:08 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Description:	get the position of first file in arguments
*/

static int	get_file_position(int argc, t_args *ls)
{
	int i;

	i = ls->opt_c;
	if ((i == 0 && argc > 1) || (argc - i >= i + 1 && i != 0))
	{
		++i;
	}
	ls->files_c = argc - i;
	return (i);
}

/*
** Description:	get an array of files, sort and get their number
**
** NOTE:		(malloc)(char **){files,*files}
*/

char		**files_parser(int argc, char **argv, t_args *ls)
{
	char	**files;
	int		i;
	int		j;

	i = get_file_position(argc, ls);
	if (!(files = (char **)malloc(sizeof(char *) * (ls->files_c))))
		exit(EXIT_FAILURE);
	j = 0;
	if (ft_strcmp(argv[i], "--") == 0)
		if (++i == argc)
			files[j++] = ft_strdup(".");
	while (i < argc)
	{
		if (ls->files_c == 1 && ls->files_c + ls->opt_c == argc)
			files[j] = ft_strdup(".");
		else
			files[j] = ft_strdup(argv[i]);
		++i;
		++j;
	}
	ls->files_c = j;
	files = get_ascii_sorted_args(ls->files_c, files);
	return (files);
}

/*
** Description:	option recognition
*/

static void	get_option(char alpha, t_opts *option)
{
	option->recursive_read = (alpha == OPTIONS[1]) ? 1 : option->recursive_read;
	option->dot_files = (alpha == OPTIONS[2]) ? 1 : option->dot_files;
	option->long_format = (alpha == OPTIONS[3]) ? 1 : option->long_format;
	option->reverse_sort = (alpha == OPTIONS[4]) ? 1 : option->reverse_sort;
	option->time_sort = (alpha == OPTIONS[5]) ? 1 : option->time_sort;
}

/*
** Description:	validation options
*/

static int	is_option(char *str, t_opts *option)
{
	size_t	len;
	size_t	i;
	size_t	j;

	if (str[0] == OPTIONS[0] && str[1])
	{
		if (str[1] == OPTIONS[0] && !str[2])
			return (EXIT_FAILURE);
		i = 1;
		len = ft_strlen(OPTIONS);
		while (str[i])
		{
			j = 1;
			while (j < len && str[i] != OPTIONS[j])
				++j;
			if (str[i] != OPTIONS[j])
			{
				ft_printf(USE_MSG, str[i], OPTIONS);
				exit(EXIT_FAILURE);
			}
			get_option(str[i++], option);
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/*
** Description:	initialize the structure with options and get the number of
** 				arguments with options
*/

int			options_parser(int argc, char **argv, t_opts *option)
{
	int	i;

	option->dot_files = 0;
	option->time_sort = 0;
	option->long_format = 0;
	option->reverse_sort = 0;
	option->recursive_read = 0;
	i = 1;
	while (i < argc && !is_option(argv[i], option))
	{
		++i;
	}
	return (i - 1);
}
