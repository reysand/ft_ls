/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 13:14:26 by fhelena           #+#    #+#             */
/*   Updated: 2020/08/24 20:20:57 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ft_ls(char *name)
{
	struct dirent	*entry;
	DIR				*dir;

	if (!(dir = opendir(name)))
	{
		ft_putstr("ft_ls: ");
		perror(name);
		return (EXIT_FAILURE);
	}
	while ((entry = readdir(dir)))
	{
		// TODO: Sort and format
		ft_printf("%s\n", entry->d_name);
	}
	(void)closedir(dir);
	return (EXIT_SUCCESS);
}

int		main(int argc, char **argv)
{
	int	i;
	int	ret;

	// TODO: Check options
	if (argc == 1)
	{
		return (ft_ls("."));
	}
	i = 1;
	ret = EXIT_SUCCESS;
	while (i < argc)
	{
		if (ft_ls(argv[i]) == 1)
			ret = EXIT_FAILURE;
		++i;
	}
	return (ret);
}
