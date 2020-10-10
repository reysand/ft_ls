/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:39 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/10 18:24:28 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <stdlib.h>
# include <sys/errno.h>
# include "libft.h"

typedef struct dirent	t_dirent;

typedef struct			s_file
{
	struct s_file		*next;
	char				*d_name;
	int					d_ino;
	int					d_type;
	int					d_reclen;
	int					d_namlen;
}						t_file;

typedef struct			s_dirlist
{
	struct s_dirlist	*next;
	t_file				*dir;
	char				*path;
}						t_dirlist;

typedef struct			s_args
{
	char				**argv;
	int					argc;
	int					ret_v;
	int					opt_c;
	int					files_c;
}						t_args;

typedef struct			s_option
{
	int					dot_files;
	int					time_sort;
	int					long_format;
	int					reverse_order;
	int					recursive_read;
}						t_option;

int						options_parser(t_args *args, t_option *option);
char					**files_parser(t_args *args);
char					**sort_args(int argc, char **argv);
int						ft_ls(char *name, t_file **file_info, t_option *option);
int						ls_recursive(char *name, t_file **file_info, t_option *option);
void					get_ascii_sort(t_file **head);
void					ls_output(t_list *not_dirs, t_dirlist *list);
void					free_matrix(char **matrix, int size);
void					free_list_strings(t_list **head);
void					free_list(t_file **head);
void					free_list_lists(t_dirlist **head);

#endif
