/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/27 19:18:17 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/07 20:21:08 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_list_strings(t_list *head)
{
	while (head)
	{
		ft_printf("%s\n", (char *)head->content);
		head = head->next;
	}
}

void	print_list(t_file *head)
{
	while (head)
	{
		ft_printf("%s\n", head->d_name);
		head = head->next;
	}
}

void	print_list_lists(int count, t_dirlist *head)
{
	while (head)
	{
		if (head->next || count > 0)
			ft_printf("%s:\n", head->path);
		print_list(head->dir);
		if (head->next)
			ft_printf("\n");
		head = head->next;
	}
}
