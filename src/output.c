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
** Function:	init_align
** Arguments:	t_align *align
** Return:		(void)
** Description:
**
** TODO:		write description
*/

void		init_align(t_align *align)
{
	align->permissions = 0;
	align->nlink = 0;
	align->user = 0;
	align->group = 0;
	align->size = 0;
}

/*
** TODO:		write description
** TODO:		add get_major()
** TODO:		add get_minor()
*/

void		long_format(t_file *head, t_align *align_max)
{
	get_mode(head->stat.st_mode);
	get_nlink(head, align_max);
	get_user(head, align_max);
	get_group(head, align_max);
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

	init_align(&align_max);
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

/*
** Function:	print_list_lists
** Arguments:	t_dirs *head, int dir_path, t_opts option
** Return:		(void)
** Description:
**
** TODO:		write description
*/

void		print_list_lists(t_dirs *head, int dir_path, t_opts option)
{
	t_dirs *first;

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
** Description:	error output requiring program exit
*/

void		err_out(char *name, t_args *ls)
{
	ls->ret_v = EXIT_FAILURE;
	ft_printf_fd(STDERR_FILENO, ERR_MSG, name, strerror(errno));
}
