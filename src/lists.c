/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:55:55 by fhelena           #+#    #+#             */
/*   Updated: 2020/12/11 14:15:25 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Function:	enotdir_add
** Arguments:	char *file, t_file **head
** Return:		(void)
** Description:	Add files to t_file structure
**
** NOTE:		(malloc){*head,(*head)->name}
*/

void	enotdir_add(char *file, t_file **head)
{
	t_file	*not_dirs;
	t_file	*item;

	if (!(item = (t_file *)malloc(sizeof(t_file))))
		exit(EXIT_FAILURE);
	item->name = ft_strdup(file);
	lstat(file, &item->stat);
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
** Function:	dir_content_add
** Arguments:	char *path, t_dirs **head, t_file *dir_info
** Return:		(void)
** Description:	Add dirs content to t_dirs structure
**
** NOTE:		(malloc){*head,(*head)->path}
*/

void	dir_content_add(char *path, t_dirs **head, t_file *dir_info)
{
	t_dirs	*dir;
	t_dirs	*item;

	if (!(item = (t_dirs *)malloc(sizeof(t_dirs))))
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
