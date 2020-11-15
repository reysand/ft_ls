/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:39 by fhelena           #+#    #+#             */
/*   Updated: 2020/11/15 17:47:03 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/errno.h>
# include <pwd.h>
# include <grp.h>
# include <limits.h>
# include <time.h>
# include "ft_ls_structs.h"
# include "libft.h"

/*
** args_parser.c
*/
void	options_parser(t_args *ls, t_opts *option);
char	**files_parser(t_args *ls);

/*
** sorting.c
*/
char	**get_ascii_sorted_args(int argc, char **argv);

/*
** main.c
*/
void	dir_handler(char *path, int rec, t_args *ls, t_opts option);

/*
** ft_ls.c
*/
int		ft_ls(char *name, t_file **file_info, t_opts option);

/*
** sorting.c
*/
void	get_sorted(t_file **head, t_opts option);
void	get_ascii_sorted(t_file **head);
void	get_reverse_sorted(t_file **head);
void	get_time_sorted(t_file **head);

/*
** lists.c
*/
void	dir_content_add(char *path, t_dirlist **head, t_file *dir_info);
void	enotdir_add(char *file, t_file **head);

/*
** output.c
*/
void	ls_output(t_file *not_dirs, t_dirlist *list, int files_c, t_opts option);

/*
** long_format.c
*/
int		get_total(t_file *head);
void	get_mode(int mode);
void	get_nlink(t_file *head, t_align *align);
void	get_user(t_file *head, t_align *align);
void	get_group(t_file *head, t_align *align);
void	get_size(t_file *head, t_align *align);
void	get_time(t_stat stat);

/*
** free.c
*/
void	free_list_lists(t_dirlist **head);
void	free_list(t_file **head);
void	free_matrix(char **matrix, int size);

/*
** Debugging
*/
char	*get_path(char *dir, char *subdir);
void	print_list(t_file *head, t_opts option);

#endif
