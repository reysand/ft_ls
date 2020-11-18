/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:10:29 by fhelena           #+#    #+#             */
/*   Updated: 2020/11/16 15:08:29 by reysand          ###   ########.fr       */
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
		time_curr = list->stat.ST_CTIME.tv_nsec;
		time_next = list->next->stat.ST_CTIME.tv_nsec;
		//ft_printf("LOGS: %d prev =\t%s\nLOGS: %d list =\t%s\n", time_curr, prev->name, time_next, list->name);
		if (time_curr < time_next)
		{
			is_sorted = 1;
			//ft_printf("LOGS: swap:\t----------\n");
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
	//ft_printf("LOGS: list =\t%s\n", list->name);
	//ft_printf("LOGS: list =\t%s\n", list->next);
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
** Description:
** Return:		(void)
*/

void			get_sorted(t_file **head, t_opts option)
{
	t_file	*prev;
	t_file	*list;
	t_file	*next;

	get_ascii_sorted(head);
	//print_list(*head);
	//ft_printf("------------\n");
	if (option.time_sort)
	{
		// if time equal only ascii sort
		get_time_sorted(head);
		//ft_printf("++++++++++\n");
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
** Description:	sorting in ascii order files in array
** Return:		(char **){argv}
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
