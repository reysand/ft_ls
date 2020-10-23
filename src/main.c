/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:44 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/23 19:42:01 by fhelena          ###   ########.fr       */
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
	{
		if (ft_strcmp(file->d_name, ".") && ft_strcmp(file->d_name, ".."))
		{
			return (0);
		}
	}
	return (1);
}

static char	*get_path(char *dir, char *subdir)
{
	char	*temp;
	char	*dir_path;

	dir_path = ft_strjoin(dir, "/");
	temp = dir_path;
	dir_path = ft_strjoin(dir_path, subdir);
	free(temp);
	return (dir_path);
}

static void	recursive_handler(char *path, t_args *ls_data, t_opts option)
{
	t_dirlist	*dirs;
	t_file		*file;
	char		*dir_path;

	dirs = ls_data->dirs;
	while (dirs)
	{
		if (!ft_strcmp(dirs->path, path))
		{
			file = dirs->dir;
			while (file)
			{
				if (!is_valid_dir(file))
				{
					dir_path = get_path(path, file->d_name);
					dir_handler(dir_path, 1, ls_data, option);
					free(dir_path);
				}
				file = file->next;
			}
			return ;
		}
		dirs = dirs->next;
	}
}

void		dir_handler(char *path, int recursion, t_args *args, t_opts option)
{
	t_file	*dir_info;
	int		ret;

	dir_info = NULL;
	if ((ret = ft_ls(path, &dir_info, option)) && !recursion)
		args->ret_v = EXIT_FAILURE;
	if (dir_info)
	{
		if (!option.time_sort && !option.reverse_order)
			get_ascii_sorted(&dir_info);
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
