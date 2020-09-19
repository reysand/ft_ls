/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 19:02:37 by fhelena           #+#    #+#             */
/*   Updated: 2020/09/19 19:09:32 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	ft_ls(char *name, t_option *option)
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
			ft_printf("%s\n", entry->d_name);
		}
	}
	closedir(dir);
	return (EXIT_SUCCESS);
}
