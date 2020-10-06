/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 12:20:03 by fhelena           #+#    #+#             */
/*   Updated: 2020/10/05 12:47:25 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "libft.h"

typedef struct			s_file
{
	struct s_file		*next;			// 8
	char				*d_name;		// 8
	int					d_ino;			// 4
	int					d_type;			// 4
	int					d_reclen;		// 4
	int					d_namlen;		// 4
}						t_file;			// 32

typedef struct			s_dirlist
{
	struct s_dirlist	*next;			// 8
	t_file				*dir;			// 8
	char				*path;			// 8
}						t_dirlist;		// 24

void	free_list(t_file *head)
{
	t_file	*list;
	t_file	*temp;

	list = head;
	while (list)
	{
		temp = list;
		list = list->next;
		free(temp->d_name);
		free(temp);
	}
}

void	free_list_lists(t_dirlist *head)
{
	t_dirlist *list;
	t_dirlist *temp;

	list = head;
	while (list)
	{
		temp = list;
		list = list->next;
		free_list(temp->dir);
		temp->dir = NULL;
		free(temp);
	}
}

int	main(void)
{
	t_dirlist	*list;
	t_dirlist	*temp;
	t_file	*file;
	t_file	*item;
	file = NULL;
	item = NULL;
	if (!(item = (t_file *)malloc(sizeof(t_file))))
		return (1);
	item->d_name = ft_strdup("result");
	item->next = NULL;
	file = item;
	if (!(temp = (t_dirlist *)malloc(sizeof(t_dirlist))))
		return (1);
	temp->path = "test";
	temp->dir = file;
	temp->next = NULL;
	list = temp;
	free_list_lists(list);
	list = NULL;
	if (list)
		ft_printf("not test\n");
	else
		ft_printf("test\n");
	return (0);
}
