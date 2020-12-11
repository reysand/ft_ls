/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:04:38 by fhelena           #+#    #+#             */
/*   Updated: 2020/12/03 05:44:46 by reysand          ###   ########.fr       */
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
	int					size;
	int					user;
	int					group;
	int					nlink;
}						t_align;

/*
** Struct:				t_file
** Description:
*/

typedef struct			s_file
{
	struct s_file		*next;
	struct stat			stat;
	char				*name;
	char				*path;
	char				*full_path;
}						t_file;

/*
** Struct:				t_dirs
** Description:
**
** NOTE: 				May be instead of add t_file to t_dirs print t_file,
** 						free them and go to next without using t_dirs.
** 						dirs change to t_file from t_dirs
*/

typedef struct			s_dirs
{
	struct s_dirs		*next;
	t_file				*dir;
	char				*path;
}						t_dirs;

/*
** Struct:				t_args
** Description:
*/

typedef struct			s_args
{
	t_dirs				*dirs;
	t_file				*files;
	t_file				*not_dirs;
	char				**argv;
	int					argc;
	int					ret_v;
	int					opt_c;
	int					files_c;
}						t_args;

/*
** Struct:				t_opts
** Description:
*/

typedef struct			s_opts
{
	int					dot_files;
	int					fs_blocks;
	int					time_sort;
	int					long_format;
	int					reverse_sort;
	int					recursive_read;
}						t_opts;

#endif
