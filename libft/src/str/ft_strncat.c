/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 11:49:16 by fhelena           #+#    #+#             */
/*   Updated: 2020/05/23 11:49:17 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t dstlen;
	size_t strlen;

	dstlen = ft_strlen(s1);
	strlen = ft_strlen(s2);
	if (strlen < n)
		n = strlen;
	ft_strncpy(s1 + dstlen, s2, n);
	s1[dstlen + n] = '\0';
	return (s1);
}
