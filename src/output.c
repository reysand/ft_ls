/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:18:17 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/23 17:52:24 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define OPTIONS	"-Ralrt"

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

void	ls_output(t_list *not_dirs, t_dirlist *dirs, int files_c)
{
	int	dir_path;

	dir_path = 0;
	print_list_strings(not_dirs);
	if (dirs && (not_dirs || files_c > 1))
	{
		dir_path = 1;
		if (not_dirs)
		{
			ft_printf("\n");
		}
	}
	free_list_strings(&not_dirs);
	print_list_lists(dirs, dir_path);
	free_list_lists(&dirs);
}

void	debug_output(t_args ls_data, t_opts options)
{
	ft_printf_fd(STDERR_FILENO, "Options\t- %d\n", ls_data.opt_c);
	ft_printf_fd(STDERR_FILENO, "Files\t- %d\n", ls_data.files_c);
	ft_printf_fd(STDERR_FILENO, "Options[%s]: ", OPTIONS);
	ft_printf_fd(STDERR_FILENO, "%d ", options.recursive_read);
	ft_printf_fd(STDERR_FILENO, "%d ", options.dot_files);
	ft_printf_fd(STDERR_FILENO, "%d ", options.long_format);
	ft_printf_fd(STDERR_FILENO, "%d ", options.reverse_order);
	ft_printf_fd(STDERR_FILENO, "%d\n", options.time_sort);
}
