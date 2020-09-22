/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 19:02:37 by fhelena           #+#    #+#             */
/*   Updated: 2020/09/19 19:09:32 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	free_list(t_file *head)
{
	t_file	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->d_name);
		free(tmp);
	}
}

static void	print_list(t_file *head)
{
	while (head != NULL)
	{
		ft_printf("%s\n", head->d_name);
		head = head->next;
	}
}

static void	get_info(t_file **head, t_dirent *entry)
{
	t_file	*files;
	t_file	*item;

	files = *head;
	if (!(item = (t_file *)malloc(sizeof(t_file))))
		return ;
	item->d_ino = entry->d_ino;
	item->d_type = entry->d_type;
	item->d_reclen = entry->d_reclen;
	item->d_namlen = entry->d_namlen;
	item->d_name = ft_strdup(entry->d_name);
	item->next = NULL;
	if (*head == NULL)
	{
		*head = item;
		return ;
	}
	while (files->next != NULL)
	{
		files = files->next;
	}
	files->next = item;
	return ;
}

int			ft_ls(char *name, t_option *option)
{
	t_dirent	*entry;
	DIR			*dir;
	t_file		*file;

	if (!(dir = opendir(name)))
	{
		if (errno == ENOTDIR)
			ft_printf("%s\n", name);
		else
			ft_printf_fd(STDERR_FILENO, "ft_ls: %s: %s\n", name, strerror(errno));
		return (EXIT_FAILURE);
	}
	file = NULL;
	while ((entry = readdir(dir)))
	{
		get_info(&file, entry);
		(void)option;
	}
	print_list(file);
	free_list(file);
	closedir(dir);
	return (EXIT_SUCCESS);
}
