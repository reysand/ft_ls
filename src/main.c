/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:44 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/21 19:58:15 by fhelena          ###   ########.fr       */
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

static void	recursive(char *path, t_args *ls_data, t_option *option)
{
	t_dirlist	*list;
	t_file		*file;
	char		*dir_path;

	list = ls_data->dirs;
	while (list)
	{
		if (!ft_strcmp(list->path, path))
		{
			file = list->dir;
			while (file)
			{
				dir_path = ft_strjoin(path, "/");
				dir_path = ft_strjoin(dir_path, file->d_name);
				recursive_read(dir_path, 1, ls_data, option);
				file = file->next;
			}
		}
		list = list->next;
	}
}

void	recursive_read(char *path, int rec, t_args *args, t_option *option)
{
	t_file	*dir_info;
	int		ret;

	dir_info = NULL;
	if (option->recursive_read && rec)
		if (is_valid(args->dirs->dir))
			return ;
	if ((ret = ft_ls(path, &dir_info, option)) && !rec)
		args->ret_v = EXIT_FAILURE;
	if (dir_info )
	{
		if (!option->time_sort && !option->reverse_order)
			get_ascii_sort(&dir_info);
		else if (option->reverse_order)
			get_reverse_sort(&dir_info);
		dir_content_add(path, &args->dirs, dir_info);
		if (option->recursive_read)
			recursive(path, args, option);
	}
	else if (!dir_info && !ret && !rec)
		enotdir_add(path, &args->not_dirs);
}

static void	args_handler(char **files, t_args *ls_data, t_option *option)
{
	int			i;

	i = 0;
	ls_data->dirs = NULL;
	ls_data->not_dirs = NULL;
	while (i < ls_data->files_c)
	{
		recursive_read(files[i], 0, ls_data, option);
		++i;
	}
	ls_output(ls_data->not_dirs, ls_data->dirs, ls_data->files_c);
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
	files = files_parser(&ls_data);          // Allocate memory for **files
	args_handler(files, &ls_data, &options);
	free_matrix(files, ls_data.files_c);     // Deallocate memory for **files
	debug_output(ls_data, options);
	return (ls_data.ret_v);
}
