/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 19:02:37 by fhelena           #+#    #+#             */
/*   Updated: 2020/11/14 16:49:30 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	get_info(char *full_path, t_file **head, t_dirent *entry)
{
	t_file	*dirs;
	t_file	*file;

	if (!(file = (t_file *)malloc(sizeof(t_file))))
		exit(EXIT_FAILURE);
	file->name = ft_strdup(entry->d_name);
	lstat(full_path, &file->stat);
	file->next = NULL;
	if (*head == NULL)
	{
		*head = file;
		return ;
	}
	dirs = *head;
	while (dirs->next)
	{
		dirs = dirs->next;
	}
	dirs->next = file;
}

char		*get_path(char *path, char *name)
{
	char	*temp;
	char	*full_path;

	full_path = ft_strjoin(path, "/");
	temp = full_path;
	full_path = ft_strjoin(full_path, name);
	free(temp);
	return (full_path);
}

int			ft_ls(char *path, t_file **dirs, t_opts option)
{
	t_dirent	*entry;
	DIR			*dir_stream;
	char		*full_path;

	if (!(dir_stream = opendir(path)))
	{
		if (errno == ENOTDIR || errno == ELOOP)
		{
			return (EXIT_SUCCESS);
		}
	}
	while ((entry = readdir(dir_stream)))
	{
		if (option.dot_files || (entry->d_name)[0] != '.')
		{
			full_path = get_path(path, entry->d_name);
			get_info(full_path, dirs, entry);
			free(full_path);
		}
	}
	if (!(*dirs))
	{
		return (EXIT_FAILURE);
	}
	closedir(dir_stream);
	return (EXIT_SUCCESS);
}
