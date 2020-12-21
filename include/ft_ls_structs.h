/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:04:38 by fhelena           #+#    #+#             */
/*   Updated: 2020/12/21 12:08:16 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_STRUCTS_H
# define FT_LS_STRUCTS_H

# include <dirent.h>
# include <sys/stat.h>

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;

typedef struct			s_align
{
	int					nlink;
	int					user;
	int					group;
	int					size;
	int					major;
	int					minor;
}						t_align;

typedef struct			s_perm
{
	int					s_read;
	int					s_write;
	int					s_exec;
	int					s_bit;
	char				is_exec;
	char				not_exec;
}						t_perm;

typedef struct			s_file
{
	struct s_file		*next;
	struct stat			stat;
	char				*name;
	char				*full_path;
}						t_file;

typedef struct			s_dirs
{
	struct s_dirs		*next;
	t_file				*dir;
	char				*path;
}						t_dirs;

typedef struct			s_args
{
	t_dirs				*dirs;
	t_file				*files;
	t_file				*not_dirs;
	int					ret_v;
	int					opt_c;
	int					files_c;
}						t_args;

typedef struct			s_opts
{
	int					dot_files;
	int					time_sort;
	int					long_format;
	int					reverse_sort;
	int					recursive_read;
}						t_opts;

#endif
