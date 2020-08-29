/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 16:49:49 by fhelena           #+#    #+#             */
/*   Updated: 2020/08/27 17:34:43 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*new_list()
{
	t_file	*new;

	if (!(new = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	new->next = NULL;
	return (new);
}

void		fill_list(t_file *file, struct dirent *entry)
{
	file->d_name = entry->d_name;
	file->d_ino = entry->d_ino;
	file->d_type = entry->d_type;
	file->d_reclen = entry->d_reclen;
	file->d_namlen = entry->d_namlen;
}
