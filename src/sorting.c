/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:10:29 by fhelena           #+#    #+#             */
/*   Updated: 2020/11/09 12:22:38 by fhelena          ###   ########.fr       */
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

/*
** function:	get_time_sorted
** arguments:	t_file **head
** description:
** return:		(void)
**
** BUG: Wrong sorting 'Makefile'
** FIXME:
** NOTE:
** TODO:
** XXX:
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
		ft_printf("LOGS: prev =\t%s\nLOGS: list =\t%s\n", prev->d_name, list->d_name);
		time_curr = (long long)list->stat.st_mtimespec.tv_sec;
		time_next = (long long)list->next->stat.st_mtimespec.tv_sec;
		if (time_curr < time_next)
		{
			is_sorted = 1;
			ft_printf("LOGS: swap:\t----------\n");
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
		{
			list = *head;
		}
	}
	ft_printf("\nLOGS: list =\t%s\n", list->d_name);
	ft_printf("LOGS: list =\t%s\n", list->next);
}

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

void			get_sorted(t_file **head, t_opts option)
{
	t_file	*prev;
	t_file	*list;
	t_file	*next;

	print_list(*head);
	ft_printf("==========\n");
	if (option.time_sort)
	{
		get_time_sorted(head);
		ft_printf("++++++++++\n");
	}
	else
		get_ascii_sorted(head);
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
