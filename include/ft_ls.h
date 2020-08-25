/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 13:15:11 by fhelena           #+#    #+#             */
/*   Updated: 2020/08/25 19:59:00 by fhelena          ###   ########.fr       */
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

typedef struct			s_options
{
	int					dot_files;
	int					time_sort;
	int					long_format;
	int					reverse_sort;
	int					recursive_read;
}						t_options;


typedef struct			s_content
{
	char				*d_name;
	int					d_ino;
	int					d_type;
	int					d_reclen;
	int					d_namlen;
	struct s_content	*next;
}						t_content;

t_content				*new_list();
void					fill_list(t_content *content, struct dirent *entry);

#endif
