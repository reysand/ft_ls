/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:39 by fhelena           #+#    #+#             */
/*   Updated: 2020/12/11 13:51:04 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <grp.h>
# include <limits.h>
# include <pwd.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <time.h>
# include "ft_ls_structs.h"
# include "libft.h"

# define OPTIONS "-Ralrt1"
# define ERR_MSG "ft_ls: %s: %s\n"

# ifdef __APPLE__
#  define IS_DIR(m) (m & S_IFDIR) == S_IFDIR
# elif __linux__
#  define IS_DIR(m) S_ISDIR(m)
# endif

void	options_parser(t_args *ls, t_opts *option);
char	**files_parser(t_args *ls);
char	**get_ascii_sorted_args(int argc, char **argv);
void	err_out(char *name, t_args *ls);
void	enotdir_add(char *file, t_file **head);
void	get_sorted(t_file **head, t_opts option);
void	dir_handler(char *path, int rec, t_args *ls, t_opts option);
int		ft_ls(char *name, t_file **file_info, t_opts option);
char	*get_path(char *dir, char *subdir);
void	dir_content_add(char *path, t_dirs **head, t_file *dir_info);
void	free_list(t_file **head);
void	ls_output(t_file *not_dirs, t_dirs *list, int files_c, t_opts option);
void	get_mode(int mode);
void	get_nlink(t_file *head, t_align *align);
void	get_user(t_file *head, t_align *align);
void	get_group(t_file *head, t_align *align);
void	get_size(t_file *head, t_align *align);
void	get_time(t_stat stat);
int		get_total(t_file *head);
void	free_list_lists(t_dirs **head);
void	free_matrix(char **matrix, int size);

#endif
