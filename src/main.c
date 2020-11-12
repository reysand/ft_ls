/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:44 by fhelena           #+#    #+#             */
/*   Updated: 2020/11/12 21:02:31 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define OPTIONS	"-Ralrt1"

static int	is_valid_dir(char *dir_path, t_file *file)
{
	stat(dir_path, &file->stat);
	if ((file->stat.st_mode & S_IFDIR) == S_IFDIR)
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
				dir_path = get_path(path, file->name);
				//ft_printf_fd(STDERR_FILENO, "LOGS: %s\n", dir_path);
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
** Function:	dir_handler
** Arguments:	char *path, int recursion, t_args *ls, t_opts option
** Description:
** Return:		(void)
**
** BUG:
** FIXME:		rename dir_handler
** NOTE:
** TODO:
** XXX:
*/

void		dir_handler(char *path, int recursion, t_args *ls, t_opts option)
{
	t_file	*dir_info;
	int		ret;

	dir_info = NULL;
	if ((ret = ft_ls(path, &dir_info, option)) && !recursion)
		ls->ret_v = EXIT_FAILURE;
	//ft_printf("LOGS: %s %d %d %d %d\n", path, !dir_info, !ret, ret, !recursion);
	if (dir_info)
	{
		get_sorted(&dir_info, option);
		dir_content_add(path, &ls->dirs, dir_info);
		if (option.recursive_read)
			recursive_handler(path, ls, option);
	}
	else if (!dir_info && ret == 2)
	{
		dir_content_add(path, &ls->dirs, dir_info);
	}
	else if (!dir_info && !ret && !recursion)
	{
		enotdir_add(path, &ls->not_dirs);
	}
}

/*
** Function:	test
** Arguments:	char **files, t_args *ls
** Description:	Test function
** Return:		(int){EXIT_SUCCESS,EXIT_FAILURE}
**
** TODO:		rename function
** TODO:		sort dirs and not dirs in different lists
*/

#define ERR_MSG "ft_ls: %s: %s\n"

int		test(char **files, t_args *ls)
{
	t_stat	f_stat;
	int		i;
	int		ret;

	i = 0;
	//ft_printf("\tFunction: test\n");
	ret = EXIT_SUCCESS;
	while (i < ls->files_c)
	{
		if (stat(files[i], &f_stat) != -1)
		{
			enotdir_add(files[i], &ls->files);
		}
		else
		{
			ret = EXIT_FAILURE;
			ft_printf_fd(STDERR_FILENO, ERR_MSG, files[i], strerror(errno));
		}
		++i;
	}
	return (ret);
}

/*
** Function:	main
** Arguments:	int argc, char **argv
** Description:
** Return:		(int){EXIT_SUCCESS,EXIT_FAILURE}
**
** BUG:
** FIXME:		rename char **files
** NOTE:
** TODO:		init of t_args struct move to another function
** XXX:
*/

int			main(int argc, char **argv)
{
	t_args	ls;
	t_file	*files_list;
	t_opts	options;
	char	**files;
	int		i;

	ls.argc = argc;
	ls.argv = argv;
	ls.files = NULL;
	ls.dirs = NULL;
	ls.not_dirs = NULL;
	ls.ret_v = EXIT_SUCCESS;
	options_parser(&ls, &options);
	files = files_parser(&ls);
	if (test(files, &ls))
		ls.ret_v = EXIT_FAILURE;
	if (ls.files)
	{
		get_sorted(&ls.files, options);
	}
	//print_list(ls.files);
	//ft_printf("$$$$$$$$$$$$$$$$\n");
	i = 0;
	files_list = ls.files;
	while (files_list)
	{
		dir_handler(files_list->name, 0, &ls, options);
		files_list = files_list->next;
	}
	free_list(&ls.files);
	if (ls.not_dirs)
	{
		get_sorted(&ls.not_dirs, options);
	}
	ls_output(ls.not_dirs, ls.dirs, ls.files_c);
	free_matrix(files, ls.files_c);
	return (ls.ret_v);
}
