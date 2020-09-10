/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/06 18:17:26 by fhelena           #+#    #+#             */
/*   Updated: 2020/09/10 20:07:03 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/errno.h>
# include "libft.h"

typedef struct dirent	t_dirent;

typedef struct stat		t_stat;

typedef struct			s_option
{
	int					dot_files;
	int					time_sort;
	int					long_format;
	int					reverse_order;
	int					recursive_read;
}						t_options;

#endif
