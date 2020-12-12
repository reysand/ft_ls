/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:10:29 by fhelena           #+#    #+#             */
/*   Updated: 2020/12/12 20:40:52 by fhelena          ###   ########.fr       */
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
		time_curr = list->stat.st_mtime;
		time_next = list->next->stat.st_mtime;
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
	t_file	**first;
	t_file	**second;

	list = *head;
	first = &(*head);
	second = &(*first)->next;
	while ((*first)->next)
	{
		ft_printf_fd(STDERR_FILENO, "%s ", (*first)->name);
		ft_printf_fd(STDERR_FILENO, "%s\n", (*second)->name);
		if (ft_strcmp((*first)->name, (*second)->name) > 0)
		{
			ft_printf_fd(STDERR_FILENO, "NEED_SWAP\t");
			*first = (*first)->next;
			ft_printf_fd(STDERR_FILENO, "%s ", (*first)->name);
			ft_printf_fd(STDERR_FILENO, "%s\n", (*second)->name);
			ft_printf_fd(STDERR_FILENO, "---open---\n");
			ft_printf_fd(STDERR_FILENO, "%s ", (*first)->next->name);
			ft_printf_fd(STDERR_FILENO, "%s\n", (*second)->next->name);
			ft_printf_fd(STDERR_FILENO, "---close---\n");
		}
		first = &(*first)->next;
		second = &(*second)->next;
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
