/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:18:17 by fhelena           #+#    #+#             */
/*   Updated: 2020/11/14 20:46:04 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define OPTIONS	"-Ralrt"

void	align(char *str, size_t max)
{
	size_t	spaces;

	spaces = max - ft_strlen(str);
	while (spaces-- > 0)
	{
		ft_printf(" ");
	}
}

void	print_list(t_file *head, t_opts option)
{
	struct passwd	*pw;
	struct group	*gr;

	while (head)
	{
		if (option.long_format)
		{
			get_mode(head->stat.st_mode);
			//align(ft_itoa(head->stat.st_nlink), 4);
			ft_printf("%4d ", head->stat.st_nlink);
			pw = getpwuid(head->stat.st_uid);
			ft_printf("%s", pw->pw_name);
			gr = getgrgid(head->stat.st_gid);
			align("", 2);
			ft_printf("%s", gr->gr_name);
			//align(ft_itoa(head->stat.st_size), 7);
			ft_printf("%7d ", head->stat.st_size);
			get_time(head->stat);
			//ft_printf(" %s ", ctime(&head->stat.st_mtime));
			//ft_printf("--- -- --:-- ");
		}
		ft_printf("%s", head->name);
		if (option.long_format && ((head->stat.st_mode & S_IFLNK) == S_IFLNK))
		{
			ft_printf(" -> ");
			//ft_printf(" -> %s", readlink(head->namei));
		}
		ft_printf("\n");
		head = head->next;
	}
}

void	print_list_lists(t_dirlist *head, int dir_path, t_opts option)
{
	t_dirlist *first;

	first = head;
	while (head)
	{
		if (first != head || dir_path)
		{
			ft_printf("%s:\n", head->path);
		}
		if (option.long_format)
		{
			ft_printf("total %d\n", get_total(head->dir));
		}
		print_list(head->dir, option);
		if (head->next)
			ft_printf("\n");
		head = head->next;
	}
}

void	ls_output(t_file *not_dirs, t_dirlist *dirs, int files_c, t_opts option)
{
	int	dir_path;

	dir_path = 0;
	print_list(not_dirs, option);
	if (dirs && (not_dirs || files_c > 1))
	{
		dir_path = 1;
		if (not_dirs)
		{
			ft_printf("\n");
		}
	}
	free_list(&not_dirs);
	print_list_lists(dirs, dir_path, option);
	free_list_lists(&dirs);
}
