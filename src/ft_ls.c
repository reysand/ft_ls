/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 13:14:26 by fhelena           #+#    #+#             */
/*   Updated: 2020/08/27 21:00:28 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define OPTIONS "-Ralrt"

static int	ft_ls(char *name, t_options *option)
{
	struct dirent	*entry;
	DIR				*dir;
	t_file			*head;
	t_file			*file;

	if (!(dir = opendir(name)))
	{
		ft_printf("ft_ls: %s: %s\n", name, strerror(errno));
		return (EXIT_FAILURE);
	}
	file = NULL;
	head = file;
	while ((entry = readdir(dir)))
	{
		head = (t_file *)malloc(sizeof(t_file));
		if ((entry->d_name)[0] != '.' && !option->dot_files)
		{
			ft_printf("%s\t", entry->d_name);
		}
	}
	(void)closedir(dir);
	return (EXIT_SUCCESS);
}

static void	parse_options(char c, t_options *option)
{
	if (c == 'a')
		option->dot_files = 1;
	else if (c == 'l')
		option->long_format = 1;
	else if (c == 'R')
		option->recursive_read = 1;
	else if (c == 'r')
		option->reverse_sort = 1;
	else if (c == 't')
		option->time_sort = 1;
	else
	{
		ft_printf("ft_ls: illegal option -- %c\n", c);
		ft_printf("usage: ft_ls [%s] [file ...]\n", OPTIONS);
		exit(EXIT_FAILURE);
	}
}

static int	is_option(char *str, t_options *option)
{
	int	i;

	if (str[0] == '-')
	{
		i = 1;
		while (str[i])
		{
			parse_options(str[i], option);
			++i;
		}
		return (0);
	}
	return (1);
}

static void	init(t_options *option)
{
	option->dot_files = 0;
	option->time_sort = 0;
	option->long_format = 0;
	option->reverse_sort = 0;
	option->recursive_read = 0;
}

int			main(int argc, char **argv)
{
	t_options	options;
	int			i;
	int			ret;
	int			options_count;

	init(&options);
	i = 1;
	options_count = 0;
	while (i < argc)
	{
		if (!is_option(argv[i], &options))
		{
			++options_count;
		}
		else if (ft_ls(argv[i], &options))
		{
			ret = EXIT_FAILURE;
		}
		++i;
	}
	if (options_count == argc - 1)
	{
		ret = ft_ls(".", &options);
	}
	return (ret);
}
