/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 11:46:22 by fhelena           #+#    #+#             */
/*   Updated: 2020/05/23 11:46:23 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_memccpy - copy memory area
*/

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*target;
	unsigned char	*source;
	unsigned char	value;

	target = (unsigned char *)dst;
	source = (unsigned char *)src;
	value = (unsigned char)c;
	while (n--)
	{
		*target++ = *source;
		if (*source++ == value)
			return ((void *)target);
	}
	return (NULL);
}
