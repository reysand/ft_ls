/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:10:29 by fhelena           #+#    #+#             */
/*   Updated: 2020/09/28 11:38:26 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_file	*swap_nodes(t_file *head)
{
	t_file	*end;
	t_file	*first;
	t_file	*second;

	first = head;
	second = first->next;
	end = second->next;
	head = second;
	second->next = first;
	first->next = end;
	return (head);
}

void			get_ascii_sort(t_file **head)
{
	t_file	*list;
	t_file	*prev;
	int		is_sorted;

	list = *head;
	while (list->next)
	{
		if (list == *head)
		{
			is_sorted = 0;
			prev = list;
		}
		if (ft_strcmp(list->d_name, list->next->d_name) > 0)
		{
			is_sorted = 1;
			if (prev == list && list == *head)
				*head = swap_nodes(list);
			else
				prev->next = swap_nodes(list);
		}
		prev = list;
		list = list->next;
		if (!list->next && is_sorted)
			list = *head;
	}
}
