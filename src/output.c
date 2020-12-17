/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:18:17 by fhelena           #+#    #+#             */
/*   Updated: 2020/12/14 20:03:23 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** TODO:		write description
** TODO:		add get_major()
** TODO:		add get_minor()
*/

static void	long_format(t_file *head, t_align *align_max)
{
	get_mode(head->stat.st_mode);
	get_nlink(head, align_max);
	get_user(head, align_max);
	get_group(head, align_max);
	get_major(head, align_max);
	get_minor(head, align_max);
	get_size(head, align_max);
	get_time(head->stat);
}

/*
** Function:	print_list
** Arguments:	t_file *head, t_opts option
** Return:		(void)
** Description:
**
** TODO:		write description
** NOTE:		(malloc){l_name}
*/

static void	print_list(t_file *head, t_opts option)
{
	t_align	align_max;
	char	*l_name;
	int		len;

	align_max.permissions = 0;
	align_max.nlink = 0;
	align_max.user = 0;
	align_max.group = 0;
	align_max.size = 0;
	align_max.major = 0;
	align_max.minor = 0;
	while (head)
	{
		if (option.long_format)
			long_format(head, &align_max);
		ft_printf("%s", head->name);
		if (option.long_format && ((head->stat.st_mode & S_IFMT) == S_IFLNK))
		{
			if (!(l_name = ft_strnew(PATH_MAX + 1)))
				return ;
			if ((len = readlink(head->full_path, l_name, PATH_MAX)) != -1)
				l_name[len] = '\0';
			ft_printf(" -> %s", l_name);
		}
		ft_printf("\n");
		head = head->next;
	}
}

static char	*get_name(char *full_path)
{
	char	**list;
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
	return (list[i - 1]);
}

/*
** Function:	print_list_lists
** Arguments:	t_dirs *head, int dir_path, t_opts option
** Return:		(void)
** Description:
**
** TODO:		write description
*/

static void	print_list_lists(t_dirs *head, int dir_path, t_opts option)
{
	t_dirs	*first;
	t_stat	f_stat;

	first = head;
	while (head)
	{
		if (first != head || dir_path)
		{
			ft_printf("%s:\n", head->path);
		}
		if (option.long_format && head->dir)
		{
			ft_printf("total %d\n", get_total(head->dir));
		}
		if (!head->dir)
		{
			/*
			 * lstat check
			 */
			lstat(head->path, &f_stat);
			if (!((f_stat.st_mode >> 8) & 1))
			{
				errno = EACCES;
				ft_printf_fd(STDERR_FILENO, ERR_MSG, get_name(head->path), strerror(errno));
			}
		}
		print_list(head->dir, option);
		if (head->next)
			ft_printf("\n");
		head = head->next;
	}
}

/*
** Function:	ls_output
** Arguments:	t_file *not_dirs, t_dirs *dirs, int files_c, t_opts option
** Return:		(void)
** Description:
**
** TODO:		write description
*/

void		ls_output(t_file *not_dirs, t_dirs *dirs, int files_c, t_opts option)
{
	int	dir_path;

	dir_path = 0;
	print_list(not_dirs, option);
	if (dirs && (not_dirs || files_c > 1))
	{
		dir_path = 1;
		if (not_dirs)
		{
			ft_printf("\n");
		}
	}
	free_list(&not_dirs);
	print_list_lists(dirs, dir_path, option);
	free_list_lists(&dirs);
}

/*
** Function:	err_out
** Arguments:	char *name, t_args *ls
** Return:		(void)
** Description:	error output
*/

void		err_out(char *name, t_args *ls)
{
	ls->ret_v = EXIT_FAILURE;
	ft_printf_fd(STDERR_FILENO, ERR_MSG, name, strerror(errno));
}
