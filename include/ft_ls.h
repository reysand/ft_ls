/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:39 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/22 20:03:41 by fhelena          ###   ########.fr       */
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
char	**args_sorting(char **files, t_args ls_data, t_opts option);
void	dir_handler(char *path, int rec, t_args *args, t_opts option);
int		ft_ls(char *name, t_file **file_info, t_opts option);
void	get_ascii_sort(t_file **head);
void	get_reverse_sort(t_file **head);
void	dir_content_add(char *name, t_dirlist **head, t_file *file_info);
void	enotdir_add(char *file, t_list **head);
void	ls_output(t_list *not_dirs, t_dirlist *list, int files_c);
void	free_list_strings(t_list **head);
void	free_list_lists(t_dirlist **head);
void	free_list(t_file **head);
void	free_matrix(char **matrix, int size);

/*
** For debugging
*/

void	print_list(t_file *head);
void	debug_output(t_args ls_data, t_opts options);

#endif
