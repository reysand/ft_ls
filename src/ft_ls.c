/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 19:02:37 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/10 17:44:51 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define ERR_MSG	"ft_ls: %s: %s\n"

static void	get_info(t_file ***head, t_dirent *entry)
{
	t_file	*files;
	t_file	*item;

	if (!(item = (t_file *)malloc(sizeof(t_file))))
		exit(EXIT_FAILURE);
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

int			ls_recursive(char *name, t_file **file_info, t_option *option)
{
	t_dirent	*entry;
	DIR			*dir;

	if (!(dir = opendir(name)))
	{
		return (EXIT_FAILURE);
	}
	while ((entry = readdir(dir)))
	{
		if (option->dot_files || (entry->d_name)[0] != '.')
		{
			get_info(&file_info, entry);
		}
	}
	closedir(dir);
	return (EXIT_SUCCESS);
}

int			ft_ls(char *name, t_file **file_info, t_option *option)
{
	t_dirent	*entry;
	DIR			*dir;

	if (!(dir = opendir(name)))
	{
		if (errno == ENOTDIR)
			return (EXIT_SUCCESS);
		else
		{
			ft_printf_fd(STDERR_FILENO, ERR_MSG, name, strerror(errno));
			return (EXIT_FAILURE);
		}
	}
	while ((entry = readdir(dir)))
	{
		if (option->dot_files || (entry->d_name)[0] != '.')
		{
			get_info(&file_info, entry);
		}
	}
	closedir(dir);
	return (EXIT_SUCCESS);
}
