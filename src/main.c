/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:44 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/20 18:47:11 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define OPTIONS	"-Ralrt"

static int	is_valid(t_file *file)
{
	if (file->d_type == DT_DIR)
		if (ft_strcmp(file->d_name, ".") && ft_strcmp(file->d_name, ".."))
			return (0);
	return (1);
}

static void	list_add(char *path, t_file *dir, t_dirlist **lst, t_option *option)
{
	if (!option->time_sort && !option->reverse_order)
		get_ascii_sort(&dir);
	else if (option->reverse_order)
		get_reverse_sort(&dir);
	dir_content_add(path, lst, dir);
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

/*
** dir_info - dir content
** list - list of dir contents
*/

static void	args_handler(char **files, t_args *ls_data, t_option *option)
{
	t_file		*dir_info;
	t_dirlist	*list;
	t_list		*not_dirs;
	int			i;
	int			ret;

	i = 0;
	list = NULL;
	not_dirs = NULL;
	while (i < ls_data->files_c)
	{
		dir_info = NULL;
		if ((ret = ft_ls(files[i], &dir_info, option)))
			ls_data->ret_v = EXIT_FAILURE;
		if (dir_info)
		{
			list_add(files[i], dir_info, &list, option);
			if (option->recursive_read)
				recursive(files[i], list, option);
		}
		else if (!dir_info && !ret)
			enotdir_add(files[i], &not_dirs);
		++i;
	}
	ls_output(not_dirs, list, ls_data->files_c);
}

/*
** files - array of dirs, existing files and non-existent files
*/

int			main(int argc, char **argv)
{
	t_args		ls_data;
	t_option	options;
	char		**files;

	ls_data.argc = argc;
	ls_data.argv = argv;
	ls_data.ret_v = EXIT_SUCCESS;
	options_parser(&ls_data, &options);
	files = files_parser(&ls_data);
	args_handler(files, &ls_data, &options);
	free_matrix(files, ls_data.files_c);
	debug_output(options);
	return (ls_data.ret_v);
}
