/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:39 by fhelena           #+#    #+#             */
/*   Updated: 2020/12/23 19:39:06 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <grp.h>
# include <pwd.h>
# include <sys/errno.h>
# include <sys/xattr.h>
# include <time.h>
# include "ft_ls_structs.h"
# include "libft.h"

# ifdef __APPLE__
#  define XATTR_OPT XATTR_NOFOLLOW
#  define LISTXATTR(_path, _list, size) listxattr(_path, _list, size, XATTR_OPT)
# elif __linux__
#  define major(x) (int)(((unsigned int)(x) >> 24) & oxff)
#  define minor(x) (int)(x & 0xffffff)
#  define LISTXATTR(_path, _list, size) listxattr(_path, _list, size)
# endif

# define PATH_MAX	1024

# define OPTIONS "-Ralrt1"
# define USE_MSG "ft_ls: illegal option -- %c\nusage: ft_ls [%s] [file ...]\n"
# define ERR_MSG "ft_ls: %s: %s\n"

int		options_parser(int argc, char **argv, t_opts *option);
char	**files_parser(int argc, char **argv, t_args *ls);
char	**get_ascii_sorted_args(int argc, char **argv);
void	check_link(char *file, t_args *ls);
int		get_matrix_size(char **matrix);
void	err_out(char *name);
void	enotdir_add(char *file, t_file **head);
void	get_sorted(t_file **head, t_opts option);
void	dir_handler(char *path, int rec, t_args *ls, t_opts option);
int		check_link_dir(char *name);
int		ft_ls(char *name, t_file **file_info, t_opts option);
char	*get_path(char *dir, char *subdir);
void	dir_content_add(char *path, t_dirs **head, t_file *dir_info);
void	free_list(t_file **head);
void	ls_output(t_file *not_dirs, t_dirs *list, int files_c, t_opts option);
void	init_align(t_align *align);
void	long_format(t_file *head, t_align *align_max);
void	get_mode(int mode);
void	get_xattr(char *name);
void	get_nlink(t_file *head, t_align *align);
void	output_align(int len, int align);
void	get_user(t_file *head, t_align *align);
int		print_user_group(char *str);
void	get_group(t_file *head, t_align *align);
void	get_major(t_file *head, t_align *align);
void	get_minor(t_file *head, t_align *align);
void	get_size(t_file *head, t_align *align);
void	get_time(t_stat stat);
int		get_total(t_file *head);
void	free_list_lists(t_dirs **head);
void	free_matrix(char **matrix, int size);

#endif
