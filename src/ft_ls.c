/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 18:16:00 by fhelena           #+#    #+#             */
/*   Updated: 2020/09/10 20:59:00 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define OPTIONS "-Ralrt"

static int	ft_ls(char *name, t_options *option)
{
	struct dirent	*entry;
	DIR				*dir;

	if (!(dir = opendir(name)))
	{
		ft_printf_fd(STDERR_FILENO, "ft_ls: %s: %s\n", name, strerror(errno));
		return (EXIT_FAILURE);
	}
	while ((entry = readdir(dir)))
	{
		if ((entry->d_name)[0] != '.' && !option->dot_files)
		{
			ft_putstr_fd(entry->d_name, 2);
			ft_putstr_fd("\n", 2);
		}
	}
	closedir(dir);
	return (EXIT_SUCCESS);
}
static char	**sort_args(int argc, char **argv)
{
	int		i;
	int		is_sorted;
	char	*tmp;

	i = 1;
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

static void	parse_options(char alpha, t_options *option)
{
	option->recursive_read = (alpha == 'R') ? 1 : option->recursive_read;
	option->dot_files = (alpha == 'a') ? 1 : option->dot_files;
	option->long_format = (alpha == 'l') ? 1 : option->long_format;
	option->reverse_order = (alpha == 'r') ? 1 : option->reverse_order;
	option->time_sort = (alpha == 't') ? 1 : option->time_sort;
}

static int	is_option(char *str, t_options *options)
{
	size_t	i;
	size_t	j;

	i = 1;
	if (str[i - 1] == '-' && str[i])
	{
		while (str[i])
		{
			j = 1;
			while (OPTIONS[j] != str[i] && j < ft_strlen(OPTIONS))
			{
				++j;
			}
			if (str[i] != OPTIONS[j])
			{
				ft_printf("ft_ls: illegal option -- %c\n", str[i]);
				ft_printf("usage: ft_ls [%s] [file ...]\n", OPTIONS);
				exit(EXIT_FAILURE);
			}
			parse_options(str[i], options);
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
	option->reverse_order = 0;
	option->recursive_read = 0;
}

int			main(int argc, char **argv)
{
	t_options	options;
	int			i;
	int			ret;
	int			option_count;

	i = 1;
	option_count = 0;
	init(&options);
	argv = sort_args(argc, argv);
	while (i < argc)
	{
		if (!is_option(argv[i], &options))
		{
			++option_count;
		}
		else if (ft_ls(argv[i], &options))
		{
			ret = EXIT_FAILURE;
		}
		ft_printf("%s\n", argv[i]);
		++i;
	}
	if (option_count == argc - 1)
	{
		ret = ft_ls(".", &options);
	}
	ft_printf("\noptc = %d\nOptions[%s]: ", option_count, OPTIONS);
	ft_printf("%d %d ", options.recursive_read, options.dot_files);
	ft_printf("%d %d ", options.long_format, options.reverse_order);
	ft_printf("%d\n", options.time_sort);
	exit(ret);
}
