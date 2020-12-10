/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 19:02:37 by fhelena           #+#    #+#             */
/*   Updated: 2020/11/15 19:59:59 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Function:	get_info
** Arguments:	char *full_path, t_file **head, t_dirent *entry
** Return:		(void)
** Description:	get all file info
**
** NOTE:		(malloc){*head,(*head)->name,(*head)->full_path}
*/

static void	get_info(char *full_path, t_file **head, t_dirent *entry)
{
	t_file	*dirs;
	t_file	*file;

	if (!(file = (t_file *)malloc(sizeof(t_file))))
		exit(EXIT_FAILURE);
	file->name = ft_strdup(entry->d_name);
	file->full_path = ft_strdup(full_path);
	lstat(full_path, &file->stat);
	file->next = NULL;
	if (!(*head))
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

/*
** Function:	get_path
** Arguments:	char *path, char *name
** Return:		(char *){full_path}
** Description:	get full path string
**
** NOTE:		(malloc){full_path}
*/

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

/*
** Function:	ft_ls
** Arguments:	char *path, t_file **dirs, t_opts option
** Return:		(int){EXIT_SUCCESS,EXIT_FAILURE}
** Description:	get a valid dir and info about its contents
*/

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
	closedir(dir_stream);
	if (!(*dirs))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
