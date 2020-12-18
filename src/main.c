/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:44 by fhelena           #+#    #+#             */
/*   Updated: 2020/12/03 05:43:58 by reysand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Description:	Check dir for recursive reading
*/

static int	is_valid_dir(char *dir_path, t_file *file)
{
	lstat(dir_path, &file->stat);
	if (S_ISDIR(file->stat.st_mode))
	{
		if (ft_strcmp(file->name, ".") && ft_strcmp(file->name, ".."))
		{
			return (0);
		}
	}
	return (1);
}

static void	recursive_handler(char *path, t_args *ls, t_opts option)
{
	t_dirs	*dirs;
	t_file	*file;
	char	*dir_path;

	dirs = ls->dirs;
	while (dirs)
	{
		if (!ft_strcmp(dirs->path, path))
		{
			file = dirs->dir;
			while (file)
			{
				dir_path = get_path(path, file->name);
				if (!is_valid_dir(dir_path, file))
				{
					dir_handler(dir_path, 1, ls, option);
				}
				free(dir_path);
				file = file->next;
			}
			return ;
		}
		dirs = dirs->next;
	}
}

void		dir_handler(char *path, int recursion, t_args *ls, t_opts option)
{
	t_file	*dir_info;
	int		ret;

	dir_info = NULL;
	ret = ft_ls(path, &dir_info, option);
	if (!recursion && !ls->ret_v && option.long_format)
	{
		if (check_link_dir(path))
		{
			dir_info = NULL;
			ret = 0;
		}
	}
	if (dir_info)
	{
		get_sorted(&dir_info, option);
		dir_content_add(path, &ls->dirs, dir_info);
		if (option.recursive_read)
			recursive_handler(path, ls, option);
	}
	else if (ret)
		dir_content_add(path, &ls->dirs, dir_info);
	else if (!recursion)
		enotdir_add(path, &ls->not_dirs);
}

/*
** Description:	check existing files and sort them
*/

static void	get_valid_files(char **files, t_args *ls, t_opts option)
{
	t_stat	f_stat;
	int		i;

	i = 0;
	ls->ret_v = EXIT_SUCCESS;
	while (i < ls->files_c)
	{
		if (lstat(files[i], &f_stat) != -1)
		{
			if (!((f_stat.st_mode >> 8) & 1))
			{
				ls->ret_v = EXIT_FAILURE;
				check_link(files[i], ls);
			}
			enotdir_add(files[i], &ls->files);
		}
		else
		{
			ls->ret_v = EXIT_FAILURE;
			err_out(files[i]);
		}
		++i;
	}
	if (ls->files)
		get_sorted(&ls->files, option);
}

int			main(int argc, char **argv)
{
	t_args	ls;
	t_file	*files_list;
	t_opts	options;
	char	**files;

	ls.argc = argc;
	ls.argv = argv;
	ls.dirs = NULL;
	ls.not_dirs = NULL;
	options_parser(&ls, &options);
	files = files_parser(&ls);
	get_valid_files(files, &ls, options);
	files_list = ls.files;
	while (files_list)
	{
		dir_handler(files_list->name, 0, &ls, options);
		files_list = files_list->next;
	}
	free_list(&ls.files);
	if (ls.not_dirs)
		get_sorted(&ls.not_dirs, options);
	ls_output(ls.not_dirs, ls.dirs, ls.files_c, options);
	free_matrix(files, ls.files_c);
	return (ls.ret_v);
}
