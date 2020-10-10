/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:44 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/10 21:03:17 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define OPTIONS	"-Ralrt"

static void	enotdir_add(char *file, t_list **head)
{
	t_list *temp;
	t_list *item;

	if (!(item = (t_list *)malloc(sizeof(t_list))))
		exit(EXIT_FAILURE);
	item->content = file;
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

static void	dir_content_add(char *name, t_dirlist **head, t_file *file_info)
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

/*
** TODO: rename function
*/
/*
void		recursive(char *path, t_dirlist *list, t_option *option, \
						int (*func)(char *, t_file **, t_option *))
{
	t_file	*file_info;

	file_info = NULL;
	func(path, &file_info, option);
	if (file_info)
	{
		get_ascii_sort(&file_info);
		dir_content_add(path, &list, file_info);
	}
}

void		recursive(char *path, t_dirlist *list, t_option *option)
{
	t_file	*file_info;

	file_info = NULL;
	ls_recursive(path, &file_info, option);
	if (file_info)
	{
		get_ascii_sort(&file_info);
		dir_content_add(path, &list, file_info);
	}
}
*/
/*
** File and option handling with creating list of files
*/

void		args_handler(char **files, t_args *args, t_option *option)
{
	t_file		*file_info;
	t_dirlist	*list;
	t_list		*not_dirs;
	char		*path;
	int			i;
	int			ret;

	i = 0;
	list = NULL;
	not_dirs = NULL;
	while (i < args->files_c)
	{
		file_info = NULL;
		if ((ret = ft_ls(files[i], &file_info, option)))
			args->ret_v = EXIT_FAILURE;
		if (file_info)
		{
			get_ascii_sort(&file_info);
			dir_content_add(files[i], &list, file_info);
			if (option->recursive_read)
			{
				t_dirlist	*temp_list;
				temp_list = list;
				while (temp_list)
				{
					t_file	*temp_dirs;
					temp_dirs = temp_list->dir;
					path = ft_strjoin(files[i], "/");
					while (temp_dirs)
					{
						path = ft_strjoin(path, temp_dirs->d_name);
						file_info = NULL;
						ls_recursive(path, &file_info, option);
						if (file_info)
						{
							get_ascii_sort(&file_info);
							dir_content_add(path, &list, file_info);
						}
						temp_dirs = temp_dirs->next;
					}
					temp_list = temp_list->next;
				}
			}
		}
		else if (!file_info && !ret)
			enotdir_add(files[i], &not_dirs);
		++i;
	}
	ls_output(not_dirs, list);
}

/*
** TODO: may be move free_matrix in anything else function
** TODO: move all initializations to another function
*/

int			main(int argc, char **argv)
{
	t_args		ls_data;
	t_option	options;
	char		**files;

	ls_data.argc = argc;
	ls_data.argv = argv;
	ls_data.ret_v = EXIT_SUCCESS;
	options.dot_files = 0;
	options.time_sort = 0;
	options.long_format = 0;
	options.reverse_order = 0;
	options.recursive_read = 0;
	options_parser(&ls_data, &options);
	files = files_parser(&ls_data);
	args_handler(files, &ls_data, &options);
	free_matrix(files, ls_data.files_c);
	ft_printf_fd(STDERR_FILENO, "Options[%s]: ", OPTIONS);
	ft_printf_fd(STDERR_FILENO, "%d ", options.recursive_read);
	ft_printf_fd(STDERR_FILENO, "%d ", options.dot_files);
	ft_printf_fd(STDERR_FILENO, "%d ", options.long_format);
	ft_printf_fd(STDERR_FILENO, "%d ", options.reverse_order);
	ft_printf_fd(STDERR_FILENO, "%d\n", options.time_sort);
	return (ls_data.ret_v);
}
