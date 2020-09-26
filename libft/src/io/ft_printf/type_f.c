/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 21:05:26 by fhelena           #+#    #+#             */
/*   Updated: 2020/09/10 01:26:10 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print(t_flags *data, char *nb, char *fl, int len)
{
	if (nb[0] != '-')
	{
		if (data->plus)
			ft_putchar_fd('+', data->fd);
		if (data->space)
			ft_putchar_fd(' ', data->fd);
		++len;
	}
	ft_putstr_fd(nb, data->fd);
	if (data->sharp && data->p_zero)
	{
		ft_putchar_fd('.', data->fd);
		++data->len;
	}
	if (!data->p_zero)
	{
		ft_putchar_fd('.', data->fd);
		++data->len;
		ft_putstr_fd(fl, data->fd);
	}
}

static void	width_parse(t_flags *data, char *nb, char *fl, int len)
{
	int	width;

	width = data->width - (len + data->prec + 1);
	if (!data->min && width >= 0)
		print_width(data, width, 'f');
	print(data, nb, fl, len);
	free(nb);
	free(fl);
	if (data->min && width >= 0)
		print_width(data, width, 'f');
	data->len += len + data->prec;
}

static char	*float_round(t_flags *data, long double f, long double tmp)
{
	long double	r;
	char		*fl;

	if (f < 0)
		f = -f;
	r = (f * (ft_power(10, data->prec + 1))) - (long long)tmp * 10;
	if (r > 5)
		fl = ptf_itoa_base((tmp + 1), 10, "0123456789", 1);
	else
		fl = ptf_itoa_base(tmp, 10, "0123456789", 1);
	return (fl);
}

static char	*prec_parse(t_flags *data, long double f)
{
	long double		tmp;
	long long int	n;
	char			*fl;
	char			*temp_fl;

	if (!data->flag && data->prec == 0)
		data->prec = 6;
	n = (long long)ft_power(10, data->prec);
	f = f - (long long)f;
	tmp = f * n;
	if (tmp < 0)
		tmp = -tmp;
	fl = float_round(data, f, tmp);
	while ((unsigned long)data->prec > ft_strlen(fl))
	{
		temp_fl = fl;
		fl = ft_strjoin("0", fl);
		free(temp_fl);
	}
	return (fl);
}

void		float_parse(t_flags *data, va_list ap)
{
	long double	f;
	long long	fl;
	char		*after;
	char		*before;
	int			len;

	len = 1;
	if (data->mod == M_BL)
		f = va_arg(ap, long double);
	else
		f = va_arg(ap, double);
	fl = (long long)f;
	while ((fl /= 10) != 0)
		++len;
	before = ptf_itoa_base((long long)f, 10, "0123456789", 1);
	if (f < 0 || data->plus || data->space)
		++len;
	after = prec_parse(data, f);
	width_parse(data, before, after, len);
}
