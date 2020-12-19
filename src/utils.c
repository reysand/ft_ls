/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 19:59:33 by fhelena           #+#    #+#             */
/*   Updated: 2020/12/17 19:59:35 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	output_align(int len, int align)
{
	while (len < align)
	{
		ft_printf(" ");
		++len;
	}
}

void	init_align(t_align *align)
{
	align->nlink = 0;
	align->user = 0;
	align->group = 0;
	align->size = 0;
	align->major = 0;
	align->minor = 0;
}

int		get_matrix_size(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		++i;
	}
	return (i);
}

int		check_link_dir(char *file)
{
	t_stat	f_stat;
	int		len;

	len = ft_strlen(file);
	lstat(file, &f_stat);
	if (S_ISLNK(f_stat.st_mode) && file[len - 1] != '/')
	{
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	check_link(char *file, t_args *ls)
{
	t_stat	f_stat;
	char	**matrix;
	char	*prev_name;
	int		len;
	int		i;

	len = ft_strlen(file);
	matrix = ft_strsplit(file, '/');
	if ((i = get_matrix_size(matrix)) > 1)
	{
		len -= ft_strlen(matrix[i - 1]);
		free_matrix(matrix, i);
		if (file[len - 1] == '/')
		{
			++len;
		}
		prev_name = ft_strsub(file, 0, len - 1);
		lstat(prev_name, &f_stat);
		free(prev_name);
		if (!((f_stat.st_mode >> 8) & 1))
		{
			ls->ret_v = EXIT_FAILURE;
			err_out(file);
		}
	}
}
