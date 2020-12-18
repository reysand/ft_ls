/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 15:29:13 by fhelena           #+#    #+#             */
/*   Updated: 2020/12/18 15:29:16 by fhelena          ###   ########.fr       */
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

	curr = head;
	if (!align->minor)
	{
		nbrlen = 0;
		while (head)
		{
			if ((temp = minor(head->stat.st_rdev)) != 0)
				if (temp < 255 && nbrlen < (temp = ft_nbrlen(temp)))
					nbrlen = temp;
			head = head->next;
		}
		if ((align->minor = nbrlen) != 0)
			align->minor = 3;
	}
	if (!S_ISCHR(curr->stat.st_mode) && !S_ISBLK(curr->stat.st_mode))
		return ;
	output_align(ft_nbrlen(minor(curr->stat.st_rdev)), align->minor);
	if (minor(curr->stat.st_rdev) > 255)
		ft_printf(" %#010x", minor(curr->stat.st_rdev));
	else
		ft_printf(" %d", minor(curr->stat.st_rdev));
}
