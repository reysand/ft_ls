/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 13:15:11 by fhelena           #+#    #+#             */
/*   Updated: 2020/08/24 20:18:35 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <errno.h>
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include "libft.h"

typedef struct	s_options
{
	int			long_format;
	int			recursive;
	int			dot;
	int			reverse;
	int			time;
}				t_options;

#endif
