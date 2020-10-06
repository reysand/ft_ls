/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:44 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/05 12:16:50 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define OPTIONS	"-Ralrt"

/*
** Adding lists to the end of a list
*/

static void	dir_list_add(char *name, t_dirlist **head, t_file *file_info)
{
	t_dirlist	*list;
	t_dirlist	*item;

	if (!(item = (t_dirlist *)malloc(sizeof(t_dirlist))))
		return ;
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
	//free_list_lists(item);
}

/*
** File and option handling with creating list of files
*/

int			args_handler(char **files, t_args *args, t_option *option)
{
	t_file		*file_info;
	t_dirlist	*list;
	int			i;
	int			ret;

	i = 0;
	ret = EXIT_SUCCESS;
	(void)files;
	file_info = NULL;
	list = NULL;
	while (i < args->files_c)
	{
		if (ft_ls(files[i], &file_info, option))
			ret = EXIT_FAILURE;
		get_ascii_sort(&file_info);
		ft_printf("\tDir content (%s):\n", files[i]);
		print_list(file_info);
		dir_list_add(files[i], &list, file_info); // Memory allocate (*list)
		free_list(&file_info);
		++i;
	}
	ft_printf("\n\tList of dir contents:\n");
	if (list) {
		ft_printf("pass\n");
		if (list->dir)
			ft_printf("pass2\n");
		else
			ft_printf("fail2\n");
	}
	else
		ft_printf("fail\n");
	//print_list_lists(list);
	/*
	free_list_lists(&list); // Memory deallocate (*list)
	list = NULL;
	*/
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
	free_matrix(files, ls_args.files_c); // Memory deallocate (**files)
	return (ret);
}
