/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 19:02:37 by fhelena           #+#    #+#             */
/*   Updated: 2020/11/07 21:37:00 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define ERR_MSG	"ft_ls: %s: %s\n"

static void	get_info(char *full_path, t_file **head, t_dirent *entry)
{
	t_file	*dir_info;
	t_file	*file_info;

	if (!(file_info = (t_file *)malloc(sizeof(t_file))))
		exit(EXIT_FAILURE);
	file_info->d_ino = entry->d_ino;
	file_info->d_type = entry->d_type;
	file_info->d_reclen = entry->d_reclen;
	file_info->d_namlen = entry->d_namlen;
	file_info->d_seekoff = entry->d_seekoff;
	file_info->d_name = ft_strdup(entry->d_name);
	stat(full_path, &file_info->stat);
	file_info->next = NULL;
	if (*head == NULL)
	{
		*head = file_info;
		return ;
	}
	dir_info = *head;
	while (dir_info->next)
	{
		dir_info = dir_info->next;
	}
	dir_info->next = file_info;
}

char		*get_path(char *dir, char *subdir)
{
	char	*temp;
	char	*dir_path;

	dir_path = ft_strjoin(dir, "/");
	temp = dir_path;
	dir_path = ft_strjoin(dir_path, subdir);
	free(temp);
	return (dir_path);
}

int			ft_ls(char *path, t_file **dir_info, t_opts option)
{
	t_dirent	*entry;
	DIR			*dir;
	char		*full_path;

	if (!(dir = opendir(path)))
	{
		if (errno == ENOTDIR)
		{
			return (EXIT_SUCCESS);
		}
		else
		{
			ft_printf_fd(STDERR_FILENO, ERR_MSG, path, strerror(errno));
			return (EXIT_FAILURE);
		}
	}
	while ((entry = readdir(dir)))
	{
		if (option.dot_files || (entry->d_name)[0] != '.')
		{
			full_path = get_path(path, entry->d_name);
			get_info(full_path, dir_info, entry);
			free(full_path);
		}
	}
	closedir(dir);
	return (EXIT_SUCCESS);
}
