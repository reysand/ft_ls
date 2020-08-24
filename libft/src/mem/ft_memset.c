/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 11:47:01 by fhelena           #+#    #+#             */
/*   Updated: 2020/05/23 11:47:02 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *memory;
	unsigned char alpha;

	memory = (unsigned char *)b;
	alpha = (unsigned char)c;
	while (len-- > 0)
		*memory++ = alpha;
	return (b);
}
