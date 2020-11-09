/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:44 by fhelena           #+#    #+#             */
/*   Updated: 2020/11/09 13:45:30 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define OPTIONS	"-Ralrt"

static int	is_valid_dir(char *dir_path, t_file *file)
{
	stat(dir_path, &file->stat);
	if ((file->stat.st_mode & S_IFDIR) == S_IFDIR)
	{
		if (ft_strcmp(file->d_name, ".") && ft_strcmp(file->d_name, ".."))
		{
			return (0);
		}
	}
	return (1);
}

static void	recursive_handler(char *path, t_args *ls, t_opts option)
{
	t_dirlist	*dirs;
	t_file		*file;
	char		*dir_path;

	dirs = ls->dirs;
	while (dirs)
	{
		if (!ft_strcmp(dirs->path, path))
		{
			file = dirs->dir;
			while (file)
			{
				dir_path = get_path(path, file->d_name);
				ft_printf_fd(STDERR_FILENO, "LOGS: %s\n", dir_path);
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

/*
** function:	dir_handler
** arguments:	char *path, int recursion, t_args *ls, t_opts option
** description:
** return:		(void)
**
** BUG:
** FIXME: rename dir_handler
** NOTE:
** TODO: init of t_args struct move to another function
** TODO: move sortings of not_dirs in another function
** XXX:
*/

void		dir_handler(char *path, int recursion, t_args *ls, t_opts option)
{
	t_file	*dir_info;
	int		ret;

	dir_info = NULL;
	if ((ret = ft_ls(path, &dir_info, option)) && !recursion)
		ls->ret_v = EXIT_FAILURE;
	if (dir_info)
	{
		get_sorted(&dir_info, option);
		dir_content_add(path, &ls->dirs, dir_info);
		if (option.recursive_read)
			recursive_handler(path, ls, option);
	}
	else if (!dir_info && !ret && !recursion)
		enotdir_add(path, &ls->not_dirs);
}

/*
** function:	main
** arguments:	int argc, char **argv
** description:
** return:		(int){EXIT_SUCCESS,EXIT_FAILURE}
**
** BUG:
** FIXME: rename char **files
** NOTE:
** TODO: init of t_args struct move to another function
** XXX:
*/

int			main(int argc, char **argv)
{
	t_args	ls;
	t_opts	options;
	char	**files;
	int		i;

	ls.argc = argc;
	ls.argv = argv;
	ls.dirs = NULL;
	ls.not_dirs = NULL;
	ls.ret_v = EXIT_SUCCESS;
	options_parser(&ls, &options);
	files = files_parser(&ls);
	i = 0;
	while (i < ls.files_c)
	{
		dir_handler(files[i], 0, &ls, options);
		++i;
	}
	if (ls.not_dirs)
	{
		get_sorted(&ls.not_dirs, options);
	}
	ls_output(ls.not_dirs, ls.dirs, ls.files_c);
	free_matrix(files, ls.files_c);
	return (ls.ret_v);
}
