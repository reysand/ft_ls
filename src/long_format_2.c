/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:33:25 by fhelena           #+#    #+#             */
/*   Updated: 2020/12/15 17:33:27 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_major(t_file *head, t_align *align)
{
	t_file	*curr;
	int		temp;
	int		nbrlen;
	int		curr_len;

	curr = head;
	if (!align->major)
	{
		nbrlen = 0;
		while (head)
		{
			temp = minor(head->stat.st_rdev);
			if (minor(temp) != 0)
				if (nbrlen < (temp = ft_nbrlen(temp)))
					nbrlen = temp;
			head = head->next;
		}
		if ((align->major = nbrlen) != 0)
			align->major = 3;
	}
	if (!S_ISCHR(curr->stat.st_mode) && !S_ISBLK(curr->stat.st_mode))
		return ;
	curr_len = ft_nbrlen(major(curr->stat.st_rdev));
	output_align(curr_len, align->major);
	ft_printf("  %d,", major(curr->stat.st_rdev));
}

void	get_group(t_file *head, t_align *align)
{
	struct group	*gr;
	t_file			*curr_file;
	int				temp;
	int				strlen;
	int				curr_len;

	curr_file = head;
	if (!align->group)
	{
		strlen = 0;
		while (head)
		{
			gr = getgrgid(head->stat.st_gid);
			if (strlen < (temp = ft_strlen(gr->gr_name)))
				strlen = temp;
			head = head->next;
		}
		align->group = strlen;
	}
	gr = getgrgid(curr_file->stat.st_gid);
	curr_len = ft_strlen(gr->gr_name);
	ft_printf("  %s", gr->gr_name);
	output_align(curr_len, align->group);
}

void	get_user(t_file *head, t_align *align)
{
	struct passwd	*pw;
	t_file			*curr_file;
	int				temp;
	int				strlen;
	int				curr_len;

	curr_file = head;
	if (!align->user)
	{
		strlen = 0;
		while (head)
		{
			pw = getpwuid(head->stat.st_uid);
			if (strlen < (temp = ft_strlen(pw->pw_name)))
				strlen = temp;
			head = head->next;
		}
		align->user = strlen;
	}
	pw = getpwuid(curr_file->stat.st_uid);
	curr_len = ft_strlen(pw->pw_name);
	ft_printf(" %s", pw->pw_name);
	output_align(curr_len, align->user);
}

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

void	get_xattr(char *file)
{
	int	xattr;

	xattr = listxattr(file, NULL, 0, XATTR_NOFOLLOW);
	if (xattr > 0)
	{
		ft_printf("@");
	}
	else
	{
		ft_printf(" ");
	}
}
