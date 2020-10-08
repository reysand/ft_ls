/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:44 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/08 12:55:51 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define OPTIONS	"-Ralrt"

static void	not_dir_add(char *file, t_list **head)
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

int			args_handler(char **files, t_args *args, t_option *option)
{
	t_file		*file_info;
	t_dirlist	*list;
	t_list		*not_dirs;
	int			i;
	int			count;
	int			temp;
	int			ret;

	i = 0;
	ret = EXIT_SUCCESS;
	list = NULL;
	not_dirs = NULL;
	while (i < args->files_c)
	{
		file_info = NULL;
		if ((temp = ft_ls(files[i], &file_info, option)))
			ret = EXIT_FAILURE;
		if (file_info)
		{
			get_ascii_sort(&file_info);
			dir_content_add(files[i], &list, file_info);
		}
		else if (!file_info && !temp)
			not_dir_add(files[i], &not_dirs);
		++i;
	}
	print_list_strings(not_dirs);
	count = 0;
	if (list && not_dirs)
	{
		ft_printf("\n");
		count = 1;
	}
	free_list_strings(&not_dirs);
	print_list_lists(count, list);
	free_list_lists(&list);
	ft_printf_fd(STDERR_FILENO, "\nOptions[%s]: %d %d %d %d %d\n", OPTIONS, \
			option->recursive_read, option->dot_files, option->long_format, \
			option->reverse_order, option->time_sort);
	return (ret);
}

int			main(int argc, char **argv)
{
	t_args		ls_args;
	t_option	options;
	char		**files;
	int			ret;

	ls_args.argc = argc;
	ls_args.argv = argv;
	options.dot_files = 0;
	options.time_sort = 0;
	options.long_format = 0;
	options.reverse_order = 0;
	options.recursive_read = 0;
	options_parser(&ls_args, &options);
	files = files_parser(&ls_args);
	files = sort_args(ls_args.files_c, files);
	ret = args_handler(files, &ls_args, &options);
	free_matrix(files, ls_args.files_c);
	return (ret);
}
