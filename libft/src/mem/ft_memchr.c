/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 11:46:27 by fhelena           #+#    #+#             */
/*   Updated: 2020/05/23 11:46:28 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *str;
	unsigned char sym;

	str = (unsigned char *)s;
	sym = (unsigned char)c;
	while (n-- > 0)
		if (*str++ == sym)
			return (--str);
	return (NULL);
}
