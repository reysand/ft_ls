/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhelena <fhelena@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 20:14:21 by fhelena           #+#    #+#             */
/*   Updated: 2020/09/10 01:23:14 by fhelena          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	prec_parse(t_flags *data, char *s)
{
	if (data->p_zero && !data->prec)
		return ;
	while (*s && data->prec--)
	{
		ft_putchar_fd(*s++, data->fd);
		++data->len;
	}
}

static void	width_parse(t_flags *data, char *s, char type)
{
	int		len;
	int		width;

	len = ft_strlen(s);
	if (s[0] == 0 && type == 'c')
		len = 1;
	if (data->prec < 0 && (type == '%' || (type == 's' && data->width)))
		width = data->width - len;
	else
		width = get_width(data, len, type);
	if (!data->min)
		print_width(data, width, type);
	if ((data->prec || data->p_zero) && type != 'c' && type != '%')
		prec_parse(data, s);
	else
	{
		if (s[0] == 0 && type == 'c')
			ft_putchar_fd('\0', data->fd);
		ft_putstr_fd(s, data->fd);
		data->len += len;
	}
	if (data->min)
		print_width(data, width, type);
}

void		percent_parse(t_flags *data, va_list ap)
{
	(void)ap;
	width_parse(data, "%", '%');
}

void		char_parse(t_flags *data, va_list ap)
{
	char	*str;

	str = ft_strnew(1);
	str[0] = (char)va_arg(ap, int);
	width_parse(data, str, 'c');
	free(str);
}

void		string_parse(t_flags *data, va_list ap)
{
	char	*str;

	str = va_arg(ap, char *);
	if (!str)
		str = "(null)";
	width_parse(data, str, 's');
}
