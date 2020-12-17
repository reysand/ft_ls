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

/*
** Function:	get_time
** Arguments:	t_stat stat
** Return:		(void)
** Description:
**
** TODO:		write description
*/

void	get_time(t_stat stat)
{
	time_t	now;
	char	*date_time;
	char	**temp_hms;
	char	**temp_time;

	time(&now);
	date_time = ctime(&stat.st_mtime);
	temp_time = ft_strsplit(date_time, ' ');
	ft_printf(" %s ", temp_time[1]);
	if (ft_nbrlen(ft_atoi(temp_time[2])) == 1)
	{
		ft_printf(" ");
	}
	ft_printf("%s ", temp_time[2]);
	if ((now - stat.st_mtime) >= 15724800 || (now - stat.st_mtime) < 0)
	{
		ft_printf(" %d ", ft_atoi(temp_time[4]));
	}
	else
	{
		temp_hms = ft_strsplit(temp_time[3], ':');
		ft_printf("%s:%s ", temp_hms[0], temp_hms[1]);
		free_matrix(temp_hms, 3);
	}
	free_matrix(temp_time, 4);
}

/*
** Function:	get_size
** Arguments:	t_file *head, t_align *align
** Return:		(void)
** Description:
**
** TODO:		write description
*/

void	get_size(t_file *head, t_align *align)
{
	t_file	*curr;
	int		temp;
	int		nbrlen;
	int		curr_len;

	curr = head;
	if (!align->size)
	{
		nbrlen = 0;
		while (head)
		{
			if (nbrlen < (temp = ft_nbrlen(head->stat.st_size)))
				nbrlen = temp;
			head = head->next;
		}
		align->size = nbrlen;
	}
	if (S_ISCHR(curr->stat.st_mode) || S_ISBLK(curr->stat.st_mode))
		return ;
	curr_len = ft_nbrlen(curr->stat.st_size);
	temp = align->size;
	if (align->major)
		temp = align->major + align->minor + 2;
	output_align(curr_len, temp);
	ft_printf("  %d", curr->stat.st_size);
}

void	get_minor(t_file *head, t_align *align)
{
	t_file	*curr;
	int		temp;
	int		nbrlen;
	int		curr_len;

	curr = head;
	if (!align->minor)
	{
		nbrlen = 0;
		while (head)
		{
			temp = minor(head->stat.st_rdev);
			if (minor(temp) != 0)
			{
				if (temp < 255 && nbrlen < (temp = ft_nbrlen(temp)))
					nbrlen = temp;
			}
			head = head->next;
		}
		align->minor = nbrlen;
		if (align->minor != 0)
			align->minor = 3;
	}
	if (!S_ISCHR(curr->stat.st_mode) && !S_ISBLK(curr->stat.st_mode))
		return ;
	curr_len = ft_nbrlen(minor(curr->stat.st_rdev));
	output_align(curr_len, align->minor);
	if (minor(curr->stat.st_rdev) > 255)
		ft_printf(" %#010x", minor(curr->stat.st_rdev));
	else
		ft_printf(" %d", minor(curr->stat.st_rdev));
}

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
			{
				if (nbrlen < (temp = ft_nbrlen(temp)))
					nbrlen = temp;
			}
			head = head->next;
		}
		align->major = nbrlen;
		if (align->major != 0)
			align->major = 3;
	}
	if (!S_ISCHR(curr->stat.st_mode) && !S_ISBLK(curr->stat.st_mode))
		return ;
	curr_len = ft_nbrlen(major(curr->stat.st_rdev));
	output_align(curr_len, align->major);
	ft_printf("  %d,", major(curr->stat.st_rdev));
}

/*
** Function:	get_user
** Arguments:	t_file *head, t_align *align
** Return:		(void)
** Description:
**
** TODO:		write description
** TODO:		limit 25 lines
*/

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

/*
** Function:	get_user
** Arguments:	t_file *head, t_align *align
** Return:		(void)
** Description:
**
** TODO:		write description
** TODO:		limit 25 lines
*/

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
