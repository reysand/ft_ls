/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 19:16:10 by fhelena           #+#    #+#             */
/*   Updated: 2020/11/14 21:07:33 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	get_total(t_file *head)
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

void	get_time(t_stat stat)
{
	time_t	now;
	time_t	temp;
	char	*date_time;
	char	**temp_hms;
	char	**temp_time;
	
	time(&now);
	date_time = ctime(&stat.st_mtime);
	temp_time = ft_strsplit(date_time, ' ');
	//ft_printf("%s ", temp_time[1]);
	if (ft_nbrlen(ft_atoi(temp_time[2])) == 1)
		ft_printf(" ");
	ft_printf("%s ", temp_time[2]);
	//ft_printf_fd(STDERR_FILENO, "%s %s\n", ctime(&now), date_time);
	if (now >= stat.st_mtime)
	{
	//	ft_printf("LOGS: test\n");
		temp = now - stat.st_mtime;
	}
	else
	{
	//	ft_printf("LOGS: test_2\n");
		temp = stat.st_mtime - now;
	}
	if (temp >= 15552000)
	{
	//	ft_printf("LOGS: time: %s\n", ctime(&temp));
		ft_printf(" %d ", ft_atoi(temp_time[4]));
	}
	else
	{
	//	ft_printf("LOGS: time_2: %s\n", ctime(&temp));
		temp_hms = ft_strsplit(temp_time[3], ':');
		ft_printf("%s:%s ", temp_hms[0], temp_hms[1]);
		free_matrix(temp_hms, 3);
	}
	free_matrix(temp_time, 4);
}
