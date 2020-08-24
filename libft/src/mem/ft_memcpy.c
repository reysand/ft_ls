/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 11:46:37 by fhelena           #+#    #+#             */
/*   Updated: 2020/05/23 11:46:38 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_memcpy - copy memory area
*/

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *target;
	unsigned char *source;

	target = (unsigned char *)dest;
	source = (unsigned char *)src;
	if (!n || dest == src)
		return (dest);
	while (n-- > 0)
		*target++ = *source++;
	return (dest);
}
