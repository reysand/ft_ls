/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:18:17 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/09 20:05:12 by fhelena          ###   ########.fr       */
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

void	print_list_lists(int count, t_dirlist *head)
{
	while (head)
	{
		if (head->next || count > 0)
			ft_printf("%s:\n", head->path);
		print_list(head->dir);
		if (head->next)
			ft_printf("\n");
		head = head->next;
	}
}

/*
** TODO: change count to something else
*/

void	ls_output(t_list *not_dirs, t_dirlist *list)
{
	int	count;

	count = 0;
	print_list_strings(not_dirs);
	if (list && not_dirs)
	{
		ft_printf("\n");
		count = 1;
	}
	free_list_strings(&not_dirs);
	print_list_lists(count, list);
	free_list_lists(&list);
}
