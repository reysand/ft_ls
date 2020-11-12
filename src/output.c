/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:18:17 by fhelena           #+#    #+#             */
/*   Updated: 2020/11/12 18:38:48 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define OPTIONS	"-Ralrt"

void	print_list(t_file *head)
{
	while (head)
	{
		ft_printf("%s\n", head->name);
		head = head->next;
	}
}

void	print_list_lists(t_dirlist *head, int dir_path)
{
	t_dirlist *first;

	first = head;
	while (head)
	{
		if (first != head || dir_path)
			ft_printf("%s:\n", head->path);
		print_list(head->dir);
		if (head->next)
			ft_printf("\n");
		head = head->next;
	}
}

void	ls_output(t_file *not_dirs, t_dirlist *dirs, int files_c)
{
	int	dir_path;

	dir_path = 0;
	print_list(not_dirs);
	if (dirs && (not_dirs || files_c > 1))
	{
		dir_path = 1;
		if (not_dirs)
		{
			ft_printf("\n");
		}
	}
	free_list(&not_dirs);
	print_list_lists(dirs, dir_path);
	free_list_lists(&dirs);
}
