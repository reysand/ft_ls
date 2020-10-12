/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:44 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/12 14:39:44 by fhelena          ###   ########.fr       */
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

static int	is_valid(t_file *file)
{
	if (file->d_type == DT_DIR)
		if (ft_strcmp(file->d_name, ".") && ft_strcmp(file->d_name, ".."))
			return (0);
	return (1);
}

static void	recursive(char *path, t_dirlist *head, t_option *option)
{
	t_dirlist	*list;
	t_file		*dir_info;
	t_file		*file;
	char		*dir_path;

	list = head;
	while (list)
	{
		if (!ft_strcmp(list->path, path))
		{
			file = list->dir;
			while (file)
			{
				dir_info = NULL;
				if (!is_valid(file))
				{
					dir_path = ft_strjoin(path, "/");
					dir_path = ft_strjoin(dir_path, file->d_name);
					ft_ls(dir_path, &dir_info, option);
					if (dir_info)
					{
						if (!option->time_sort && !option->reverse_order)
							get_ascii_sort(&dir_info);
						dir_content_add(dir_path, &list, dir_info);
						recursive(dir_path, list, option);
					}
				}
				file = file->next;
			}
		}
		list = list->next;
	}
}

static void	args_handler(char **files, t_args *args, t_option *option)
{
	t_file		*dir_info;
	t_dirlist	*list;
	t_list		*not_dirs;
	int			i;
	int			ret;

	i = 0;
	list = NULL;
	not_dirs = NULL;
	while (i < args->files_c)
	{
		dir_info = NULL;
		if ((ret = ft_ls(files[i], &dir_info, option)))
			args->ret_v = EXIT_FAILURE;
		if (dir_info)
		{
			if (!option->time_sort && !option->reverse_order)
				get_ascii_sort(&dir_info);
			dir_content_add(files[i], &list, dir_info);
			if (option->recursive_read)
				recursive(files[i], list, option);
		}
		else if (!dir_info && !ret)
			enotdir_add(files[i], &not_dirs);
		++i;
	}
	ls_output(not_dirs, list);
}

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
