/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 20:28:51 by fhelena           #+#    #+#             */
/*   Updated: 2020/09/10 01:26:27 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	prec_parse(t_flags *data, char *str, int length)
{
	if (data->p_zero && length == 1 && str[0] == '0')
		return ;
	if (data->prec > length)
		print_prec(data, data->prec - length, 'd');
	ft_putstr_fd(str, data->fd);
	data->len += length;
}

static void	print_specials(t_flags *data, int negative_value)
{
	if (data->space && !data->plus)
	{
		ft_putchar_fd(' ', data->fd);
		++data->len;
	}
	if (data->w_zero && !data->prec)
	{
		print_sign(data, negative_value);
	}
}

static int	check_width(t_flags *data, int len, int negative_value, char type)
{
	int	width;

	width = 0;
	if (data->prec >= len)
		width = get_width(data, data->prec + negative_value, type);
	else if (data->width)
		width = get_width(data, len + negative_value, type);
	if ((data->plus || data->space) && !negative_value && width)
		--width;
	return (width);
}

static void	width_parse(t_flags *data, char *s, char type)
{
	int	len;
	int	width;
	int	negative_value;

	len = ft_strlen(s);
	negative_value = 0;
	if (s[0] == '-')
	{
		negative_value = 1;
		++s;
		--len;
	}
	width = check_width(data, len, negative_value, type);
	if (!data->min)
	{
		print_specials(data, negative_value);
		print_width(data, width, type);
	}
	if ((!data->w_zero && !data->prec) || data->prec || data->min)
		print_sign(data, negative_value);
	prec_parse(data, s, len);
	if (data->min)
		print_width(data, width, type);
}

/*
** Conversion Specifier: d, i
** Width is the minimum number of digits
** Precision is the minimum number of digits
** If precision is 0 and the number is 0 then nothing is output
** Flag ' ' is ignored when flag '+' is present
** Flag '0' is ignored when flag '-' is present
** Flag '#' results in undefined behavior
*/

void		int_parse(t_flags *data, va_list ap)
{
	long long	decimal;
	char		*str;

	if (data->mod == M_LL)
		decimal = va_arg(ap, long long);
	else if (data->mod == M_L)
		decimal = va_arg(ap, long);
	else if (data->mod == M_H)
		decimal = (short)va_arg(ap, int);
	else if (data->mod == M_HH)
		decimal = (char)va_arg(ap, int);
	else
		decimal = va_arg(ap, int);
	str = ptf_itoa_base(decimal, 10, "0123456789", 1);
	width_parse(data, str, 'd');
	free(str);
}
