/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:55:55 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/27 20:44:23 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Adding files to the end of the list
*/

void	enotdir_add(char *file, t_list **head)
{
	t_list *not_dirs;
	t_list *item;

	if (!(item = (t_list *)malloc(sizeof(t_list))))
		exit(EXIT_FAILURE);
	item->content = file;
	item->content_size = sizeof(char *);
	item->next = NULL;
	if (*head)
	{
		not_dirs = *head;
		while (not_dirs->next)
			not_dirs = not_dirs->next;
		not_dirs->next = item;
	}
	else
	{
		*head = item;
	}
}

/*
** Adding lists of directory contents to the end of the list
*/

void	dir_content_add(char *path, t_dirlist **head, t_file *dir_info)
{
	t_dirlist	*dir;
	t_dirlist	*item;

	if (!(item = (t_dirlist *)malloc(sizeof(t_dirlist))))
		exit(EXIT_FAILURE);
	item->path = ft_strdup(path);
	item->dir = dir_info;
	item->next = NULL;
	if (*head)
	{
		dir = *head;
		while (dir->next)
			dir = dir->next;
		dir->next = item;
	}
	else
	{
		*head = item;
	}
}
