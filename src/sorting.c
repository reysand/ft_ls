/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:10:29 by fhelena           #+#    #+#             */
/*   Updated: 2020/12/13 19:00:31 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Function:	swap_nodes
** Arguments:	t_file *head
** Return:		(t_file *){head}
** Description:	swap two nodes in the t_file structure
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
** Description:	sort files and dirs by modification time
*/

void			get_time_sorted(t_file **head)
{
	t_file		**curr;
	t_file		*list;
	int			is_sorted;

	curr = &(*head);
	while ((*curr)->next)
	{
		if (curr == head)
		{
			is_sorted = 0;
			list = (*head)->next;
		}
		if ((*curr)->stat.st_mtime < list->stat.st_mtime)
		{
			is_sorted = 1;
			*curr = swap_nodes(*curr);
			list = (*curr)->next;
		}
		curr = &(*curr)->next;
		list = list->next;
		if (!list && is_sorted)
			curr = &(*head);
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
	t_file	**curr;
	t_file	*list;
	int		is_sorted;

	curr = &(*head);
	while ((*curr)->next)
	{
		if (curr == head)
		{
			is_sorted = 0;
			list = (*head)->next;
		}
		if (ft_strcmp((*curr)->name, list->name) > 0)
		{
			is_sorted = 1;
			*curr = swap_nodes(*curr);
			list = (*curr)->next;
		}
		curr = &(*curr)->next;
		list = list->next;
		if (!list && is_sorted)
			curr = &(*head);
	}
}

/*
** Function:	get_sorted
** Arguments:	t_file **head, t_opts option
** Return:		(void)
** Description:	sort in ascii and, if necessary, in time and in reverse order
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
** Description:	sorting files array in ascii order
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
