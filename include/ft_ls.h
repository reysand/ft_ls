/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:39 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/27 20:31:01 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdlib.h>
# include <sys/errno.h>
# include "ft_ls_structs.h"
# include "libft.h"

void	options_parser(t_args *ls_data, t_opts *option);
char	**files_parser(t_args *args);
char	**get_ascii_sorted_args(int argc, char **argv);
void	dir_handler(char *path, int rec, t_args *args, t_opts option);
int		ft_ls(char *name, t_file **file_info, t_opts option);
void	get_ascii_sorted(t_file **head);
void	get_time_sorted(t_file **head);
void	dir_content_add(char *path, t_dirlist **head, t_file *dir_info);
void	enotdir_add(char *file, t_list **head);
void	ls_output(t_list *not_dirs, t_dirlist *list, int files_c);
void	free_list_strings(t_list **head);
void	free_list_lists(t_dirlist **head);
void	free_list(t_file **head);
void	free_matrix(char **matrix, int size);

/*
** For debugging
*/

char	*get_path(char *dir, char *subdir);
void	debug_output(t_args ls_data, t_opts options);

#endif
