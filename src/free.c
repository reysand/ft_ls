/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:13:40 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/07 20:30:09 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Freeing matrix memory
*/

void	free_matrix(char **matrix, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(matrix[i]);
		++i;
	}
	free(matrix);
}

void	free_list_strings(t_list **head)
{
	t_list	*next;

	while (*head)
	{
		next = (*head)->next;
		ft_memdel((void *)head);
		*head = next;
	}
}

/*
** Freeing the memory of a singly linked list
*/

void	free_list(t_file **head)
{
	t_file	*next;

	while (*head)
	{
		next = (*head)->next;
		free((*head)->d_name);
		ft_memdel((void *)head);
		*head = next;
	}
}

/*
** Freeing the memory of a singly linked list of singly linked lists
*/

void	free_list_lists(t_dirlist **head)
{
	t_dirlist	*next;

	while (*head)
	{
		next = (*head)->next;
		free_list(&((*head)->dir));
		ft_memdel((void *)head);
		*head = next;
	}
}
