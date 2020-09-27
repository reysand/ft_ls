/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 19:02:37 by fhelena           #+#    #+#             */
/*   Updated: 2020/09/27 19:37:49 by fhelena          ###   ########.fr       */
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
		{
			ft_printf("%s\n", name);
			return (EXIT_SUCCESS);
		}
		else
		{
			ft_printf_fd(STDERR_FILENO, str_error, name, strerror(errno));
			return (EXIT_FAILURE);
		}
	}
	while ((entry = readdir(dir)))
		if (option->dot_files)
			get_info(&file, entry);
		else if ((entry->d_name)[0] != '.')
			get_info(&file, entry);
	closedir(dir);
	return (EXIT_SUCCESS);
}
