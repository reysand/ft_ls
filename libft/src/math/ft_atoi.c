/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 11:45:19 by fhelena           #+#    #+#             */
/*   Updated: 2020/05/23 11:45:20 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int nbr;
	int negative;

	nbr = 0;
	negative = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v' || \
			*str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			negative = -1;
	while (ft_isdigit(*str))
		nbr = nbr * 10 + (int)(*str++ - '0');
	return (nbr * negative);
}
