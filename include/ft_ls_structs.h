/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:04:38 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/22 16:32:33 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_STRUCTS_H
# define FT_LS_STRUCTS_H

# include <dirent.h>
#include <ft_list.h>

typedef struct dirent	t_dirent;

typedef struct			s_file
{
	struct s_file		*next;
	char				*d_name;
	int					d_ino;
	int					d_type;
	int					d_reclen;
	int					d_namlen;
	int					d_seekoff;
	int	temp;
}						t_file;

typedef struct			s_dirlist
{
	struct s_dirlist	*next;
	t_file				*dir;
	char				*path;
}						t_dirlist;

typedef struct			s_args
{
	t_dirlist			*dirs;
	t_list				*not_dirs;
	char				**argv;
	int					argc;
	int					ret_v;
	int					opt_c;
	int					files_c;
}						t_args;

typedef struct			s_opts
{
	int					dot_files;
	int					time_sort;
	int					long_format;
	int					reverse_order;
	int					recursive_read;
}						t_opts;

#endif
