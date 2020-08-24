/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 11:49:55 by fhelena           #+#    #+#             */
/*   Updated: 2020/05/23 11:49:56 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_nextword(char const *s, char c)
{
	while (*s == c && *s)
		++s;
	return ((char *)s);
}

static size_t	ft_wordlen(char const *s, char c)
{
	size_t i;

	i = 0;
	while (s[i] != c && s[i])
		++i;
	return (i);
}

static char		*ft_arraycpy(char const *s, char c)
{
	char	*item;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_wordlen(s, c);
	if (!(item = (char *)ft_memalloc(len + 1)))
		return (NULL);
	while (i < len)
		item[i++] = *s++;
	return (item);
}

static void		ft_arrayfree(char **list, size_t size)
{
	while (size--)
	{
		ft_strdel(&list[size]);
	}
	ft_strdel(list);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t		i;
	size_t		words;
	char		**list;

	if (!s)
		return (NULL);
	words = ft_wordcount((char *)s, c);
	if (!(list = (char **)ft_memalloc(sizeof(char *) * (words + 1))))
		return (NULL);
	i = 0;
	while (i < words)
	{
		s = ft_nextword(s, c);
		if (!(list[i] = ft_arraycpy(s, c)))
		{
			ft_arrayfree(list, i);
			return (NULL);
		}
		++i;
		s += (ft_wordlen(s, c) + 1);
	}
	list[words] = NULL;
	return (list);
}
