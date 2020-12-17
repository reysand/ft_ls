/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 19:16:10 by fhelena           #+#    #+#             */
/*   Updated: 2020/12/14 13:03:27 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Function:	get_mode
** Arguments:	t_file *head, t_align *align
** Return:		(void)
** Description:
**
** TODO:		write description
*/

void	get_nlink(t_file *head, t_align *align)
{
	t_file	*curr_file;
	int		temp;
	int		nbrlen;
	int		curr_len;

	curr_file = head;
	if (!align->nlink)
	{
		nbrlen = 0;
		while (head)
		{
			if (nbrlen < (temp = ft_nbrlen(head->stat.st_nlink)))
				nbrlen = temp;
			head = head->next;
		}
		align->nlink = nbrlen;
	}
	curr_len = ft_nbrlen(curr_file->stat.st_nlink);
	output_align(curr_len, align->nlink);
	ft_printf(" %d", curr_file->stat.st_nlink);
}

/*
** acl function
*/

/*
** Function:	get_mode_perm
** Arguments:	int mode
** Return:		(void)
** Description:	output permissions value
**
** TODO:		write description
** TODO:		rename function
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
** Function:	perm_init
** Arguments:	char who, t_mode *perm
** Return:		(void)
** Description:	init t_perm struct for each permissions group
**
** TODO:		write description
** TODO:		rename function
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
** Function:	get_mode
** Arguments:	int mode
** Return:		(void)
** Description:	get file entry type
**
** TODO:		write description
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
	ft_printf(" ");
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
