/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 16:49:49 by fhelena           #+#    #+#             */
/*   Updated: 2020/08/25 19:22:53 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_content	*new_list()
{
	t_content	*new;

	if (!(new = (t_content *)malloc(sizeof(t_content))))
		return (NULL);
	new->next = NULL;
	return (new);
}

void		fill_list(t_content *content, struct dirent *entry)
{
	content->d_name = entry->d_name;
	content->d_ino = entry->d_ino;
	content->d_type = entry->d_type;
	content->d_reclen = entry->d_reclen;
	content->d_namlen = entry->d_namlen;
}
