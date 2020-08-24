/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 11:49:43 by fhelena           #+#    #+#             */
/*   Updated: 2020/05/23 11:49:44 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*str;
	char	*sub;
	size_t	size;
	size_t	crashme;

	str = (char *)haystack;
	sub = (char *)needle;
	size = ft_strlen(sub);
	if (size == 0)
		return (str);
	crashme = ft_strlen(str);
	++crashme;
	while (*str && len-- >= size)
	{
		if (ft_strncmp(str, sub, size) == 0)
			return (str);
		++str;
	}
	return (NULL);
}
