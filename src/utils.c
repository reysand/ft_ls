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

void		output_align(int len, int align)
{
	while (len < align)
	{
		ft_printf(" ");
		++len;
	}
}

static int	get_matrix_count(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		++i;
	}
	return (i);
}

void		check_link(char *file, t_args *ls)
{
	t_stat	f_stat;
	char	**matrix;
	char	*prev_name;
	int		len;
	int		i;

	len = ft_strlen(file);
	matrix = ft_strsplit(file, '/');
	i = get_matrix_count(matrix);
	if (i > 1)
	{
		len -= ft_strlen(matrix[i - 1]);
		if (file[len - 1] == '/')
		{
			++len;
		}
		prev_name = ft_strsub(file, 0, len - 1);
		lstat(prev_name, &f_stat);
		free(prev_name);
		if (!((f_stat.st_mode >> 8) & 1))
		{
			err_out(file, ls);
		}
	}
	free_matrix(matrix, i);
}
