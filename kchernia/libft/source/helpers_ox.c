/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_ox.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 20:41:55 by kchernia          #+#    #+#             */
/*   Updated: 2018/08/25 19:53:06 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

size_t	get_total_len_ux(t_ull num, t_format *frmt, size_t *numlen)
{
	size_t	len;

	len = *numlen;
	if (frmt->prec && frmt->precision > len)
		len = frmt->precision;
	if (frmt->flags.hash == 1 && (num != 0 || frmt->is_ptr))
		len += 2;
	if (frmt->is_ptr && num == 0 && frmt->prec && frmt->precision == 0)
	{
		*numlen = 0;
		len = frmt->width - 1;
	}
	else if (frmt->width > len ||
			(frmt->prec && frmt->precision == 0 && num == 0))
		len = frmt->width;
	return (len);
}

size_t	get_total_len_uo(t_ull num, t_format *frmt, size_t numlen)
{
	size_t	len;
	t_ull	tmp;

	len = numlen;
	tmp = len;
	if (frmt->prec && frmt->precision > len)
		len = frmt->precision;
	if (frmt->width > len || (frmt->prec && frmt->precision == 0 && num == 0
		&& !frmt->flags.hash))
		len = frmt->width;
	if (frmt->flags.hash == 1 && num != 0)
	{
		if (len <= tmp)
			len++;
		else if (frmt->precision > 0)
			frmt->precision--;
	}
	return (len);
}

size_t	ft_put_alter_form(t_format *frmt, size_t index)
{
	if (TO_HEX(frmt->type))
	{
		frmt->arg[index] = frmt->type;
		frmt->arg[index - 1] = '0';
		return (2);
	}
	else if (TO_OCT(frmt->type))
	{
		frmt->arg[index] = '0';
		return (1);
	}
	else if (TO_BINARY(frmt->type))
	{
		frmt->arg[index] = 'b';
		frmt->arg[index - 1] = '0';
		return (2);
	}
	else
		return (0);
}

void	get_alter_form(t_format *frmt, size_t i1, size_t i2)
{
	if (frmt->flags.zero == 1)
		ft_put_alter_form(frmt, i2);
	else
		ft_put_alter_form(frmt, i1);
}
