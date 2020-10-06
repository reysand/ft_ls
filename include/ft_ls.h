/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:39 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/05 11:23:06 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <stdlib.h>
# include <sys/errno.h>
# include "libft.h"

typedef struct dirent	t_dirent;		// 1048

typedef struct			s_file
{
	struct s_file		*next;			// 8
	char				*d_name;		// 8
	int					d_ino;			// 4
	int					d_type;			// 4
	int					d_reclen;		// 4
	int					d_namlen;		// 4
}						t_file;			// 32

typedef struct			s_dirlist
{
	struct s_dirlist	*next;			// 8
	t_file				*dir;			// 8
	char				*path;			// 8
}						t_dirlist;		// 24

typedef struct			s_args
{
	char				**argv;			// 8
	int					argc;			// 4
	int					temp;			// 4
	int					opt_c;			// 4
	int					files_c;		// 4
}						t_args;			// 24

typedef struct			s_option
{
	int					dot_files;		// 4
	int					time_sort;		// 4
	int					long_format;	// 4
	int					reverse_order;	// 4
	int					recursive_read;	// 4
}						t_option;		// 20

int						options_parser(t_args *args, t_option *option);
char					**files_parser(t_args *args);
char					**sort_args(int argc, char **argv);
int						ft_ls(char *name, t_file **file, t_option *option);
void					get_ascii_sort(t_file **head);
void					print_list_lists(t_dirlist *head);
void					print_list(t_file *head);
void					free_matrix(char **matrix, int size);
void					free_list(t_file **head);
void					free_list_lists(t_dirlist **head);

#endif
