/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:39 by fhelena           #+#    #+#             */
/*   Updated: 2020/09/28 12:52:18 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <stdlib.h>
# include <sys/errno.h>
# include "libft.h"

typedef struct dirent	t_dirent;

typedef struct			s_args
{
	char				**argv;
	int					argc;
	int					files_c;
	int					opt_c;
	int					tmp_todo_delete;
}						t_args;

typedef struct			s_option
{
	int					dot_files;
	int					time_sort;
	int					long_format;
	int					reverse_order;
	int					recursive_read;
}						t_option;

typedef struct			s_file
{
	char				*d_name;
	int					d_ino;
	int					d_reclen;
	int					d_type;
	int					d_namlen;
	struct s_file		*next;
}						t_file;

int						options_parser(t_args *args, t_option *option);
char					**files_parser(t_args *args);
int						ft_ls(char *name, t_file **file, t_option *option, int i, int ret);
void					get_ascii_sort(t_file **head);
void					print_list(t_file *head);
void					free_list(t_file *head);

#endif
