/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 11:46:55 by fhelena           #+#    #+#             */
/*   Updated: 2020/05/23 11:46:57 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char *target;
	unsigned char *source;

	target = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (target == source)
		return (dst);
	if (src < dst)
	{
		source = (unsigned char *)src + len - 1;
		target = dst + len - 1;
		while (len--)
			*target-- = *source--;
	}
	else
		while (len--)
			*target++ = *source++;
	return (dst);
}
