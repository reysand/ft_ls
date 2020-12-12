/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:18:17 by fhelena           #+#    #+#             */
/*   Updated: 2020/12/03 05:56:35 by reysand          ###   ########.fr       */
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

void	init_align(t_align *align)
{
	align->size = 0;
	align->user = 0;
	align->group = 0;
	align->nlink = 0;
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

void	print_list(t_file *head, t_opts option)
{
	t_align	align_max;
	char	*l_name;
	int		len;

	init_align(&align_max);
	while (head)
	{
		if (option.long_format)
		{
			get_mode(head->stat.st_mode);
			get_nlink(head, &align_max);
			get_user(head, &align_max);
			get_group(head, &align_max);
			get_size(head, &align_max);
			get_time(head->stat);
		}
		ft_printf("%s", head->name);
		if (option.long_format && ((head->stat.st_mode & S_IFMT) == S_IFLNK))
		{
			if (!(l_name = ft_strnew(PATH_MAX + 1)))
				return ;
			if ((len = readlink(head->full_path, l_name, PATH_MAX)) != -1)
				l_name[len] = '\0';
			else
				ft_printf_fd(STDERR_FILENO, "%s\n", strerror(errno));
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

void	print_list_lists(t_dirs *head, int dir_path, t_opts option)
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

void	ls_output(t_file *not_dirs, t_dirs *dirs, int files_c, t_opts option)
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
