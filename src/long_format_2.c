/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 17:33:25 by fhelena           #+#    #+#             */
/*   Updated: 2020/12/24 19:36:46 by fhelena          ###   ########.fr       */
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
			temp = MAJOR(head->stat.st_rdev);
			if (MAJOR(temp) != 0)
				if (nbrlen < (temp = ft_nbrlen(temp)))
					nbrlen = temp;
			head = head->next;
		}
		if ((align->major = nbrlen) != 0)
			align->major = 3;
	}
	if (!S_ISCHR(curr->stat.st_mode) && !S_ISBLK(curr->stat.st_mode))
		return ;
	curr_len = ft_nbrlen(MAJOR(curr->stat.st_rdev));
	output_align(curr_len, align->major);
	ft_printf("  %d,", MAJOR(curr->stat.st_rdev));
}

void	get_group(t_file *head, t_align *align)
{
	struct group	*gr;
	t_file			*file;
	int				temp;
	int				len;

	file = head;
	if (!align->group)
	{
		len = 0;
		while (file)
		{
			gr = getgrgid(file->stat.st_gid);
			if (len < (temp = ft_strlen(gr->gr_name)))
				len = temp;
			file = file->next;
		}
		align->group = len;
	}
	if ((gr = getgrgid(head->stat.st_gid)))
		len = print_user_group(gr->gr_name);
	else
		len = print_user_group(ft_itoa(head->stat.st_gid));
	output_align(len, align->group);
}

void	get_user(t_file *head, t_align *align)
{
	struct passwd	*pw;
	t_file			*file;
	int				temp;
	int				len;

	file = head;
	if (!align->user)
	{
		len = 0;
		while (file)
		{
			if ((pw = getpwuid(file->stat.st_uid)))
				if (len < (temp = ft_strlen(pw->pw_name)))
					len = temp;
			file = file->next;
		}
		align->user = len + 1;
	}
	if ((pw = getpwuid(head->stat.st_uid)))
		len = print_user_group(pw->pw_name);
	else
		len = print_user_group(ft_itoa(head->stat.st_uid));
	output_align(len, align->user);
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

	xattr = LISTXATTR(file, NULL, 0);
	if (xattr > 0)
	{
		ft_printf("@");
	}
	else
	{
		ft_printf(" ");
	}
}
