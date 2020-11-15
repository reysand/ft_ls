/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 19:16:10 by fhelena           #+#    #+#             */
/*   Updated: 2020/11/15 17:25:36 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

void	get_size(t_file *head, t_align *align)
{
	t_file	*curr_file;
	int		temp;
	int		nbrlen;
	int		curr_len;

	curr_file = head;
	if (!align->size)
	{
		nbrlen = 0;
		while (head)
		{
			if (nbrlen < (temp = ft_nbrlen(head->stat.st_size)))
				nbrlen = temp;
			head = head->next;
		}
		align->size = nbrlen + 2;
	}
	curr_len = ft_nbrlen(curr_file->stat.st_size);
	while (curr_len < align->size)
	{
		ft_printf(" ");
		++curr_len;
	}
	ft_printf("%d", curr_file->stat.st_size);
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
		align->group = strlen + 2;
	}
	gr = getgrgid(curr_file->stat.st_gid);
	curr_len = ft_strlen(gr->gr_name);
	while (curr_len < align->group)
	{
		ft_printf(" ");
		++curr_len;
	}
	ft_printf("%s", gr->gr_name);
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
		align->user = strlen + 1;
	}
	pw = getpwuid(curr_file->stat.st_uid);
	curr_len = ft_strlen(pw->pw_name);
	while (curr_len < align->user)
	{
		ft_printf(" ");
		++curr_len;
	}
	ft_printf("%s", pw->pw_name);
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
		align->nlink = nbrlen + 2;
	}
	curr_len = ft_nbrlen(curr_file->stat.st_nlink);
	while (curr_len < align->nlink)
	{
		ft_printf(" ");
		++curr_len;
	}
	ft_printf("%d", curr_file->stat.st_nlink);
}

void	get_mode(int mode)
{
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
	mode & S_IRUSR ? ft_printf("r") : ft_printf("-");
	mode & S_IWUSR ? ft_printf("w") : ft_printf("-");
	mode & S_IXUSR ? ft_printf("x") : ft_printf("-");
	mode & S_IRGRP ? ft_printf("r") : ft_printf("-");
	mode & S_IWGRP ? ft_printf("w") : ft_printf("-");
	mode & S_IXGRP ? ft_printf("x") : ft_printf("-");
	mode & S_IROTH ? ft_printf("r") : ft_printf("-");
	mode & S_IWOTH ? ft_printf("w") : ft_printf("-");
	mode & S_IXOTH ? ft_printf("x") : ft_printf("-");
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
