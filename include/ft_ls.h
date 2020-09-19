/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 13:08:39 by fhelena           #+#    #+#             */
/*   Updated: 2020/09/19 16:02:42 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/errno.h>
# include "libft.h"

typedef struct	s_args
{
	char		**argv;
	int			argc;
	int			files_count;
	int			option_count;
	int			sthelse;
}				t_args;

typedef struct	s_option
{
	int			dot_files;
	int			time_sort;
	int			long_format;
	int			reverse_order;
	int			recursive_read;
}				t_option;

int				options_parser(t_args *args, t_option *option);
char			**files_parser(t_args *args);
int				ft_ls(char *name, t_option *option);

#endif
