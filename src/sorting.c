/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:10:29 by fhelena           #+#    #+#             */
/*   Updated: 2020/12/03 08:21:17 by reysand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Function:	swap_nodes
** Arguments:	t_file *head
** Return:		(t_file *){head}
** Description:	swap two nodes in t_file structure
*/

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

/*
** Function:	get_time_sorted
** Arguments:	t_file **head
** Return:		(void)
** Description:	sort files and dirs by modify time
**
** TODO:		limit 25 lines
*/

void			get_time_sorted(t_file **head)
{
	t_file		*list;
	t_file		*prev;
	long long	time_curr;
	long long	time_next;
	int			is_sorted;

	list = *head;
	while (list->next)
	{
		if (list == *head)
		{
			is_sorted = 0;
			prev = list;
		}
		time_curr = list->stat.ST_MTIME;
		time_next = list->next->stat.ST_MTIME;
		if (time_curr < time_next)
		{
			is_sorted = 1;
			if (list == *head)
			{
				*head = swap_nodes(list);
				prev = *head;
				list = (*head)->next;
			}
			else
			{
				prev->next = swap_nodes(list);
				list = prev->next->next;
				prev = prev->next;
			}
		}
		else
		{
			prev = list;
			list = list->next;
		}
		if (!list->next && is_sorted)
			list = *head;
	}
}

/*
** Function:	get_ascii_sorted
** Arguments:	t_file **head
** Return:		(void)
** Description:	sort files and dirs in ascii order
*/

void			get_ascii_sorted(t_file **head)
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
		if (ft_strcmp(list->name, list->next->name) > 0)
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

/*
** Function:	get_sorted
** Arguments:	t_file **head, t_opts option
** Return:		(void)
** Description:	sort in ascii and if needed by tine and reverse order
*/

void			get_sorted(t_file **head, t_opts option)
{
	t_file	*prev;
	t_file	*list;
	t_file	*next;

	get_ascii_sorted(head);
	if (option.time_sort)
	{
		get_time_sorted(head);
	}
	if (option.reverse_sort)
	{
		prev = NULL;
		list = *head;
		next = NULL;
		while (list)
		{
			next = list->next;
			list->next = prev;
			prev = list;
			list = next;
		}
		*head = prev;
	}
}

/*
** Function:	get_ascii_sorted_args
** Arguments:	int argc, char **argv
** Return:		(char **){argv}
** Description:	sorting in ascii order files in array
*/

char			**get_ascii_sorted_args(int argc, char **argv)
{
	char	*temp;
	int		i;
	int		is_sorted;

	i = 0;
	is_sorted = 0;
	while (i < argc - 1)
	{
		if (ft_strcmp(argv[i], argv[i + 1]) > 0)
		{
			temp = argv[i];
			argv[i] = argv[i + 1];
			argv[i + 1] = temp;
			is_sorted = 1;
		}
		++i;
		if (i == argc - 1 && is_sorted)
		{
			i = 0;
			is_sorted = 0;
		}
	}
	return (argv);
}
