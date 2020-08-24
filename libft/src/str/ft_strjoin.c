/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 11:48:41 by fhelena           #+#    #+#             */
/*   Updated: 2020/05/23 11:48:42 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sub;
	size_t	len;

	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		return ((char *)s1);
	if (!s1)
		return ((char *)s2);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(sub = (char *)ft_memalloc(len + 1)))
		return (NULL);
	ft_strcpy(sub, s1);
	ft_strcpy(sub + ft_strlen(s1), s2);
	sub[len] = '\0';
	return (sub);
}
