/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 19:16:10 by fhelena           #+#    #+#             */
/*   Updated: 2020/12/18 13:28:36 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Description:	output permissions value
*/

void	get_mode_perm(int mode, t_perm perm)
{
	char	exec_v;

	mode & perm.s_read ? ft_printf("r") : ft_printf("-");
	mode & perm.s_write ? ft_printf("w") : ft_printf("-");
	if (mode & perm.s_bit)
	{
		if (mode & perm.s_exec)
			exec_v = perm.is_exec;
		else
			exec_v = perm.not_exec;
	}
	else
	{
		if (mode & perm.s_exec)
			exec_v = 'x';
		else
			exec_v = '-';
	}
	ft_printf("%c", exec_v);
}

/*
** Description:	init t_perm struct for each permissions group
*/

void	perm_init(char who, t_perm *perm)
{
	if (who == 'u')
	{
		perm->s_read = S_IRUSR;
		perm->s_write = S_IWUSR;
		perm->s_exec = S_IXUSR;
		perm->s_bit = S_ISUID;
		perm->is_exec = 's';
		perm->not_exec = 'S';
	}
	else if (who == 'g')
	{
		perm->s_read = S_IRGRP;
		perm->s_write = S_IWGRP;
		perm->s_exec = S_IXGRP;
		perm->s_bit = S_ISGID;
	}
	else
	{
		perm->s_read = S_IROTH;
		perm->s_write = S_IWOTH;
		perm->s_exec = S_IXOTH;
		perm->s_bit = S_ISVTX;
		perm->is_exec = 't';
		perm->not_exec = 'T';
	}
}

/*
** Description:	get file entry type
*/

void	get_mode(int mode)
{
	t_perm	perm;

	if (S_ISDIR(mode))
		ft_printf("d");
	else if (S_ISCHR(mode))
		ft_printf("c");
	else if (S_ISBLK(mode))
		ft_printf("b");
	else if (S_ISFIFO(mode))
		ft_printf("p");
	else if (S_ISLNK(mode))
		ft_printf("l");
	else if (S_ISSOCK(mode))
		ft_printf("s");
	else
		ft_printf("-");
	perm_init('u', &perm);
	get_mode_perm(mode, perm);
	perm_init('g', &perm);
	get_mode_perm(mode, perm);
	perm_init('o', &perm);
	get_mode_perm(mode, perm);
}

int		get_total(t_file *head)
{
	int	total;

	total = 0;
	while (head)
	{
		total += head->stat.st_blocks;
		head = head->next;
	}
	return (total);
}

void	long_format(t_file *head, t_align *align_max)
{
	get_mode(head->stat.st_mode);
	get_xattr(head->full_path);
	get_nlink(head, align_max);
	get_user(head, align_max);
	get_group(head, align_max);
	get_major(head, align_max);
	get_minor(head, align_max);
	get_size(head, align_max);
	get_time(head->stat);
}
