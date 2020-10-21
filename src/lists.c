/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 17:55:55 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/20 18:14:02 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	enotdir_add(char *file, t_list **head)
{
	t_list *temp;
	t_list *item;

	if (!(item = (t_list *)malloc(sizeof(t_list))))
		exit(EXIT_FAILURE);
	item->content = file;
	item->content_size = sizeof(char *);
	item->next = NULL;
	if (*head)
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = item;
	}
	else
	{
		*head = item;
	}
}

/*
** Adding lists of directory contents to the end of the list
*/

void	dir_content_add(char *name, t_dirlist **head, t_file *file_info)
{
	t_dirlist	*list;
	t_dirlist	*item;

	if (!(item = (t_dirlist *)malloc(sizeof(t_dirlist))))
		exit(EXIT_FAILURE);
	item->path = name;
	item->dir = file_info;
	item->next = NULL;
	if (*head)
	{
		list = *head;
		while (list->next)
			list = list->next;
		list->next = item;
	}
	else
	{
		*head = item;
	}
}
