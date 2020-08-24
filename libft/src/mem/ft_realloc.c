/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 11:47:06 by fhelena           #+#    #+#             */
/*   Updated: 2020/05/23 11:47:07 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void *newptr;

	if (!ptr)
	{
		if (!(newptr = ft_memalloc(size)))
			return (NULL);
		return (newptr);
	}
	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	if (!(newptr = ft_memalloc(size)))
	{
		free(ptr);
		return (NULL);
	}
	ft_memcpy(newptr, ptr, size);
	ft_memdel(ptr);
	return (newptr);
}
