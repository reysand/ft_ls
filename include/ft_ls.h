/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:39 by fhelena           #+#    #+#             */
/*   Updated: 2020/11/10 20:50:08 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/errno.h>
# include "ft_ls_structs.h"
# include "libft.h"

/*
** args_parser.c
*/
void	options_parser(t_args *ls_data, t_opts *option);
char	**files_parser(t_args *args);

/*
** sorting.c
*/
char	**get_ascii_sorted_args(int argc, char **argv);

/*
** main.c
*/
void	dir_handler(char *path, int rec, t_args *args, t_opts option);

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
void	ls_output(t_file *not_dirs, t_dirlist *list, int files_c);

/*
** free.c
*/
void	free_list_strings(t_file **head);
void	free_list_lists(t_dirlist **head);
void	free_list(t_file **head);
void	free_matrix(char **matrix, int size);

/*
** Debugging
*/
char	*get_path(char *dir, char *subdir);
void	print_list(t_file *head);

#endif
