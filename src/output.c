/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:18:17 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/10 18:12:26 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Prints files that are not directories
*/

void	print_list_strings(t_list *head)
{
	while (head)
	{
		ft_printf("%s\n", (char *)head->content);
		head = head->next;
	}
}

/*
** Prints files that are the contents of a directory
*/

void	print_list(t_file *head)
{
	while (head)
	{
		ft_printf("%s\n", head->d_name);
		head = head->next;
	}
}

/*
** Prints lists of directory contents with formatting
*/

void	print_list_lists(t_dirlist *head)
{
	t_dirlist *first;

	first = head;
	while (head)
	{
		if (!(!head->next && head == first))
			ft_printf("%s:\n", head->path);
		print_list(head->dir);
		if (head->next)
			ft_printf("\n");
		head = head->next;
	}
}

void	ls_output(t_list *not_dirs, t_dirlist *list)
{
	print_list_strings(not_dirs);
	if (list && not_dirs)
	{
		ft_printf("\n");
	}
	free_list_strings(&not_dirs);
	print_list_lists(list);
	free_list_lists(&list);
}
