/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:44 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/22 20:08:01 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define OPTIONS	"-Ralrt"

/*
** Check a valid dir for recursive reading
*/

static int	is_valid_dir(t_file *file)
{
	if (file->d_type == DT_DIR)
		if (ft_strcmp(file->d_name, ".") && ft_strcmp(file->d_name, ".."))
			return (0);
	return (1);
}

static void	recursive_handler(char *path, t_args *ls_data, t_opts option)
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
				dir_handler(dir_path, 1, ls_data, option);
				file = file->next;
			}
		}
		list = list->next;
	}
}

void		dir_handler(char *path, int recursion, t_args *args, t_opts option)
{
	t_file	*dir_info;
	int		ret;

	dir_info = NULL;
	if (option.recursive_read && recursion)
		if (is_valid_dir(args->dirs->dir))
			return ;
	if ((ret = ft_ls(path, &dir_info, option)) && !recursion)
		args->ret_v = EXIT_FAILURE;
	if (dir_info)
	{
		if (!option.time_sort && !option.reverse_order)
			get_ascii_sort(&dir_info);
		if (option.reverse_order)
			get_ascii_sort(&dir_info); // reverse
		dir_content_add(path, &args->dirs, dir_info);
		if (option.recursive_read)
			recursive_handler(path, args, option);
	}
	else if (!dir_info && !ret && !recursion)
		enotdir_add(path, &args->not_dirs);
}

/*
** files - array of dirs, existing files and non-existent files
*/

int			main(int argc, char **argv)
{
	t_args	ls_data;
	t_opts	options;
	int		i;
	char	**files;

	ls_data.argc = argc;
	ls_data.argv = argv;
	ls_data.dirs = NULL;
	ls_data.not_dirs = NULL;
	ls_data.ret_v = EXIT_SUCCESS;
	options_parser(&ls_data, &options);
	files = files_parser(&ls_data);
	files = args_sorting(files, ls_data, options);
	i = 0;
	while (i < ls_data.files_c)
	{
		dir_handler(files[i], 0, &ls_data, options);
		++i;
	}
	ls_output(ls_data.not_dirs, ls_data.dirs, ls_data.files_c);
	free_matrix(files, ls_data.files_c);
	debug_output(ls_data, options);
	return (ls_data.ret_v);
}
