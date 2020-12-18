/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:13:40 by fhelena           #+#    #+#             */
/*   Updated: 2020/12/13 14:34:57 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Description:	freeing memory from the matrix
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

/*
** Description:	freeing memory from the t_file structure
*/

void	free_list(t_file **head)
{
	t_file	*next;

	while (*head)
	{
		next = (*head)->next;
		free((*head)->name);
		free((*head)->full_path);
		ft_memdel((void *)head);
		*head = next;
	}
}

/*
** Description:	freeing memory from the t_dirs structure
*/

void	free_list_lists(t_dirs **head)
{
	t_dirs	*next;

	while (*head)
	{
		next = (*head)->next;
		free((*head)->path);
		free_list(&((*head)->dir));
		ft_memdel((void *)head);
		*head = next;
	}
}
