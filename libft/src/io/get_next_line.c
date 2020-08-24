/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 11:42:51 by fhelena           #+#    #+#             */
/*   Updated: 2020/05/23 11:43:30 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*check_file(char *file, char **line)
{
	char	*ptr;

	ptr = NULL;
	if (file)
		if ((ptr = ft_strchr(file, '\n')))
		{
			*ptr = '\0';
			*line = ft_strdup(file);
			ft_strcpy(file, ++ptr);
		}
		else
		{
			*line = ft_strdup(file);
			ft_strclr(file);
		}
	else
		*line = ft_strnew(1);
	return (ptr);
}

static int		get_line(const int fd, char **line, char **file)
{
	char	buf[BUFF_SIZE + 1];
	char	*ptr;
	char	*temp;
	int		size;

	size = 1;
	ptr = check_file(*file, line);
	while (!ptr && (size = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[size] = '\0';
		if ((ptr = ft_strchr(buf, '\n')))
		{
			*ptr = '\0';
			temp = *file;
			*file = ft_strdup(++ptr);
			free(temp);
		}
		temp = *line;
		*line = ft_strjoin(*line, buf);
		free(temp);
		if (!line || size < 0)
			return (-1);
	}
	return (size || ft_strlen(*line)) ? 1 : 0;
}

static t_list	*new_list(const int fd)
{
	t_list	*new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new->content_size = fd;
	new->content = NULL;
	new->next = NULL;
	return (new);
}

static void		del_list(const int fd, t_list **head)
{
	t_list	*prev;
	t_list	*list;

	if (*head == NULL)
		return ;
	list = *head;
	prev = list;
	while (list->content_size != (size_t)fd)
	{
		prev = list;
		list = list->next;
	}
	if (list->content_size == (size_t)fd)
	{
		if (list == *head)
			*head = list->next;
		else
			prev->next = list->next;
		free(list->content);
		free(list);
	}
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*head = NULL;
	t_list			*file;
	int				ret;

	if (fd < 0 || !line || BUFF_SIZE < 1 || read(fd, NULL, 0))
		return (-1);
	if (!head)
		if (!(head = new_list(fd)))
			return (-1);
	file = head;
	while (file->content_size != (size_t)fd)
	{
		if (!file->next)
			if (!(file->next = new_list(fd)))
				return (-1);
		file = file->next;
	}
	ret = get_line(file->content_size, line, (char **)&file->content);
	if (ret == 0 || ret == -1)
		del_list(fd, &head);
	return (ret);
}
