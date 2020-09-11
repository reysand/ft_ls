/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:44 by fhelena           #+#    #+#             */
/*   Updated: 2020/09/11 15:51:52 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define OPTIONS	"-Ralrt"

static int	is_option(char *str)
{
	size_t	i;
	size_t	j;

	i = 1;
	if (str[i - 1] == '-' && str[i])
	{
		if (str[i] == '-' && !str[i + 1])
		{
			return (EXIT_FAILURE);
		}
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
			++i;
		}
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int			main(int argc, char **argv)
{
	char	**files;
	int		i;
	int		j;

	i = 1;
	while (i < argc && !is_option(argv[i]))
	{
		ft_printf("opts: %s\n", argv[i]);
		++i;
	}
	files = (char **)malloc(sizeof(char *) * (argc - i));
	j = 0;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "--") != 0)
		{
			files[j] = ft_strdup(argv[i]);
		}
		else
		{
			files[j] = ft_strdup(".");
		}
		ft_printf("file: %s\n", files[j]);
		++i;
		++j;
	}
	return (0);
}
