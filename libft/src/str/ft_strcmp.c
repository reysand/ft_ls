/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 11:48:02 by fhelena           #+#    #+#             */
/*   Updated: 2020/05/23 11:48:03 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char *str1;
	const unsigned char *str2;
	unsigned char		c1;
	unsigned char		c2;

	str1 = (const unsigned char *)s1;
	str2 = (const unsigned char *)s2;
	c1 = 0;
	c2 = 0;
	while (*str1 && *str2)
	{
		c1 = (unsigned char)*str1++;
		c2 = (unsigned char)*str2++;
		if (c1 != c2 || c1 == '\0')
			return (c1 - c2);
	}
	return (*str1 - *str2);
}
