/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:44 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/09 20:45:25 by fhelena          ###   ########.fr       */
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
** File and option handling with creating list of files
*/

void		args_handler(char **files, t_args *args, t_option *option)
{
	t_file		*file_info;
	t_dirlist	*list;
	t_list		*not_dirs;
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
		}
		else if (!file_info && !ret)
			enotdir_add(files[i], &not_dirs);
		++i;
	}
	ls_output(not_dirs, list);
}

void		ls_init(t_dirlist *list, t_list *not_dirs, t_option *options)
{
	list = NULL;
	not_dirs = NULL;
	options->dot_files = 0;
	options->time_sort = 0;
	options->long_format = 0;
	options->reverse_order = 0;
	options->recursive_read = 0;
}

/*
** Main function
** TODO: may be move free_matrix in anything else function
** TODO: t_dirlist and t_list
*/

int			main(int argc, char **argv)
{
	t_args		ls_args;
	t_option	options;
	t_dirlist	list;
	t_list		not_dirs;
	char		**files;

	ls_args.argc = argc;
	ls_args.argv = argv;
	ls_args.ret_v = EXIT_SUCCESS;
	ls_init(&list, &not_dirs, &options);
	options_parser(&ls_args, &options);
	files = files_parser(&ls_args);
	files = sort_args(ls_args.files_c, files);
	args_handler(files, &ls_args, &options);
	free_matrix(files, ls_args.files_c);
	ft_printf_fd(STDERR_FILENO, "Options[%s]: ", OPTIONS);
	ft_printf_fd(STDERR_FILENO, "%d ", options.recursive_read);
	ft_printf_fd(STDERR_FILENO, "%d ", options.dot_files);
	ft_printf_fd(STDERR_FILENO, "%d ", options.long_format);
	ft_printf_fd(STDERR_FILENO, "%d ", options.reverse_order);
	ft_printf_fd(STDERR_FILENO, "%d\n", options.time_sort);
	return (ls_args.ret_v);
}
