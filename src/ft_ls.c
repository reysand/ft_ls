/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 19:02:37 by fhelena           #+#    #+#             */
/*   Updated: 2020/09/26 19:46:13 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		free_list(t_file *head)
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

void		print_list(t_file *head)
{
	while (head != NULL)
	{
		ft_printf("%s\n", head->d_name);
		head = head->next;
	}
}

t_file		*swap(t_file *first, t_file *second)
{
	t_file	*temp;
	t_file	*end;

	temp = first;
	end = second->next;
	first = second;
	first->next = temp;
	temp->next = end;
	return (first);
}

void		sort_list(t_file **head)
{
	t_file	*file;
	t_file	*start;
	int		is_sorted;

	file = *head;
	start = *head;
	is_sorted = 0;
	while (file->next)
	{
		if (ft_strcmp(file->d_name, file->next->d_name) > 0)
		{
			is_sorted = 1;
			start->next = swap(file, file->next);
		}
		start = file;
		file = file->next;
		if (!file->next && is_sorted)
		{
			file = *head;
			start = *head;
			is_sorted = 0;
		}
	}
}

static void	get_info(t_file ***head, t_dirent *entry)
{
	t_file	*files;
	t_file	*item;

	if (!(item = (t_file *)malloc(sizeof(t_file))))
		return ;
	item->d_ino = entry->d_ino;
	item->d_type = entry->d_type;
	item->d_reclen = entry->d_reclen;
	item->d_namlen = entry->d_namlen;
	item->d_name = ft_strdup(entry->d_name);
	item->next = NULL;
	if (**head == NULL)
	{
		**head = item;
		return ;
	}
	files = **head;
	while (files->next)
	{
		files = files->next;
	}
	files->next = item;
}

int			ft_ls(char *name, t_file **file, t_option *option)
{
	t_dirent	*entry;
	DIR			*dir;
	char		*str_error;

	str_error = "ft_ls: %s: %s\n";
	if (!(dir = opendir(name)))
	{
		if (errno == ENOTDIR)
			ft_printf("%s\n", name);
		else
			ft_printf_fd(STDERR_FILENO, str_error, name, strerror(errno));
		return (EXIT_FAILURE);
	}
	while ((entry = readdir(dir)))
	{
		get_info(&file, entry);
		(void)option;
	}
	closedir(dir);
	return (EXIT_SUCCESS);
}
