/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:18:17 by fhelena           #+#    #+#             */
/*   Updated: 2020/12/22 20:11:57 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_list(t_file *head, t_opts option)
{
	t_align	align_max;
	char	*l_name;
	int		len;

	init_align(&align_max);
	while (head)
	{
		if (option.long_format)
		{
			long_format(head, &align_max);
		}
		ft_printf("%s", head->name);
		if (option.long_format && ((head->stat.st_mode & S_IFMT) == S_IFLNK))
		{
			if (!(l_name = ft_strnew(PATH_MAX + 1)))
				return ;
			if ((len = readlink(head->full_path, l_name, PATH_MAX)) != -1)
				l_name[len] = '\0';
			ft_printf(" -> %s", l_name);
			free(l_name);
		}
		ft_printf("\n");
		head = head->next;
	}
}

static char	*get_name(char *full_path)
{
	char	**list;
	char	*name;
	int		len;
	int		i;

	len = ft_strlen(full_path);
	list = ft_strsplit(full_path, '/');
	i = 0;
	while (list[i])
	{
		++i;
	}
	if (full_path[len - 1] == '/')
		return ("");
	name = ft_strdup(list[i - 1]);
	free_matrix(list, i);
	return (name);
}

static void	print_list_lists(t_dirs *head, int dir_path, t_opts option)
{
	t_dirs	*first;
	t_stat	f_stat;
	char	*name;

	first = head;
	while (head)
	{
		if (first != head || dir_path)
			ft_printf("%s:\n", head->path);
		if (option.long_format && head->dir)
			ft_printf("total %d\n", get_total(head->dir));
		if (!head->dir)
		{
			if ((lstat(head->path, &f_stat)) != -1 && errno == EACCES)
			{
				err_out((name = get_name(head->path)));
				free(name);
			}
		}
		print_list(head->dir, option);
		if (head->next)
			ft_printf("\n");
		head = head->next;
	}
}

void		ls_output(t_file *no_dirs, t_dirs *dirs, int files_c, t_opts option)
{
	int	dir_path;

	dir_path = 0;
	print_list(no_dirs, option);
	if (dirs && (no_dirs || files_c > 1))
	{
		dir_path = 1;
		if (no_dirs)
		{
			ft_printf("\n");
		}
	}
	free_list(&no_dirs);
	print_list_lists(dirs, dir_path, option);
	free_list_lists(&dirs);
}

/*
** Description:	error output
*/

void		err_out(char *name)
{
	ft_printf_fd(STDERR_FILENO, ERR_MSG, name, strerror(errno));
}
