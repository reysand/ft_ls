/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:39 by fhelena           #+#    #+#             */
/*   Updated: 2020/12/04 13:35:13 by reysand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <grp.h>
# include <limits.h>
# include <pwd.h>
# include <sys/errno.h>
# include <time.h>
# include "ft_ls_structs.h"
# include "libft.h"

# define OPTIONS "-Ralrst"
# define ERR_MSG "ft_ls: %s %s\n"

# ifdef __APPLE_
#  define IS_DIR(m) (m & S_IFDIR) == S_IFDIR
#  define ST_CTIME st_timespec
# elif __linux__
#  define IS_DIR(m) S_ISDIR(m)
#  define ST_CTIME st_ctim
# endif

/*
** File:	args_parser.c
*/
void	options_parser(t_args *ls, t_opts *option);
char	**files_parser(t_args *ls);

/*
** File:	sorting.c
*/
char	**get_ascii_sorted_args(int argc, char **argv);

/*
** File:	main.c
*/
void	dir_handler(char *path, int rec, t_args *ls, t_opts option);

/*
** File:	ft_ls.c
*/
int		ft_ls(char *name, t_file **file_info, t_opts option);

/*
** File:	sorting.c
*/
void	get_sorted(t_file **head, t_opts option);
void	get_ascii_sorted(t_file **head);
void	get_reverse_sorted(t_file **head);
void	get_time_sorted(t_file **head);

/*
** File:	lists.c
*/
void	dir_content_add(char *path, t_dirs **head, t_file *dir_info);
void	enotdir_add(char *file, t_file **head);

/*
** File:	output.c
*/
void	ls_output(t_file *not_dirs, t_dirs *list, int files_c, t_opts option);

/*
** File:	long_format.c
*/
int		get_total(t_file *head);
void	get_mode(int mode);
void	get_nlink(t_file *head, t_align *align);
void	get_user(t_file *head, t_align *align);
void	get_group(t_file *head, t_align *align);
void	get_size(t_file *head, t_align *align);
void	get_time(t_stat stat);

/*
** File:	free.c
*/
void	free_list_lists(t_dirs **head);
void	free_list(t_file **head);
void	free_matrix(char **matrix, int size);

/*
** NOTE:	Debugging
** TODO:	Delete
*/
char	*get_path(char *dir, char *subdir);
void	print_list(t_file *head, t_opts option);

#endif
