/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 18:17:26 by fhelena           #+#    #+#             */
/*   Updated: 2020/09/08 14:38:42 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/errno.h>
# include <stdio.h> // TODO: delete
# include "libft.h"

typedef struct		s_options
{
	int				dot_files;
	int				time_sort;
	int				long_format;
	int				reverse_order;
	int				recursive_read;
}					t_options;

typedef struct		s_file
{
	int				d_ino;
	int				d_type;
	int				d_reclen;
	int				d_namlen;
	char			*d_name;
	struct s_file	*next;
}					t_file;

#endif
