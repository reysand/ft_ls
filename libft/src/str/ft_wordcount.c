/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 11:50:16 by fhelena           #+#    #+#             */
/*   Updated: 2020/05/23 11:50:17 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_wordcount(char *str, char sym)
{
	int status;
	int words;

	status = 0;
	words = 0;
	while (*str)
	{
		if (*str == sym && status == 1)
			status = 0;
		if (*str++ != sym && status == 0)
		{
			status = 1;
			words++;
		}
	}
	return (words);
}
