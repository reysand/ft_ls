/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:13:40 by fhelena           #+#    #+#             */
/*   Updated: 2020/11/11 17:24:09 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

void	free_list(t_file **head)
{
	t_file	*next;

	while (*head)
	{
		next = (*head)->next;
		free((*head)->name);
		ft_memdel((void *)head);
		*head = next;
	}
}

void	free_list_lists(t_dirlist **head)
{
	t_dirlist	*next;

	while (*head)
	{
		next = (*head)->next;
		free((*head)->path);
		free_list(&((*head)->dir));
		ft_memdel((void *)head);
		*head = next;
	}
}
