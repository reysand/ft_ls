/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 13:14:26 by fhelena           #+#    #+#             */
/*   Updated: 2020/08/25 20:23:41 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	ft_ls(char *name, t_options *option)
{
	struct dirent	*entry;
	DIR				*dir;

	if (!(dir = opendir(name)))
	{
		ft_printf("ft_ls: %s: %s\n", name, strerror(errno));
		return (EXIT_FAILURE);
	}
	while ((entry = readdir(dir)))
	{
		if ((entry->d_name)[0] != '.' && !option->dot_files)
		{
			ft_printf("%s\t", entry->d_name);
		}
	}
	(void)closedir(dir);
	return (EXIT_SUCCESS);
}

static int	is_option(char *str, t_options *option)
{
	int	i;

	if (str[0] == '-')
	{
		i = 1;
		while (str[i])
		{
			if (str[i] == 'a')
				option->dot_files = 1;
			else if (str[i] == 'l')
				option->long_format = 1;
			else if (str[i] == 'R')
				option->recursive_read = 1;
			else if (str[i] == 'r')
				option->reverse_sort = 1;
			else if (str[i] == 't')
				option->time_sort = 1;
			else
			{
				ft_printf("ft_ls: illegal option -- %c\n", str[i]);
				ft_printf("usage: ft_ls [-Ralrt] [file ...]\n");
				exit(EXIT_FAILURE);
			}
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
