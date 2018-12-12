/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_frmt_signed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 18:52:33 by kchernia          #+#    #+#             */
/*   Updated: 2018/08/25 17:48:45 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static size_t	ft_numlen(t_ll num)
{
	size_t	i;
	t_ll	n;

	i = 0;
	n = num;
	if (n == 0)
		return (1);
	if (n < 0)
		n = n * -1;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static size_t	get_total_len(t_ll num, t_format *frmt)
{
	size_t	len;

	len = 0;
	len = ft_numlen(num);
	if (frmt->precision > len)
		len = frmt->precision;
	if (((frmt->flags.plus == 1 || frmt->flags.space == 1) && num >= 0)
		|| num < 0)
		++len;
	if (frmt->width > len || (frmt->prec && frmt->precision == 0 && num == 0))
		len = frmt->width;
	return (len);
}

static void		ft_putnum(t_format *frmt, t_ll num, int i, size_t precision)
{
	size_t	number_length;
	int		digit;

	number_length = ft_numlen(num);
	if (frmt->prec && frmt->precision == 0 && num == 0)
		number_length = 0;
	while (number_length > 0 || precision > 0)
	{
		if (number_length == 0 && precision > 0)
			frmt->arg[i--] = '0';
		else
		{
			digit = (num % 10);
			if (digit < 0)
				digit *= -1;
			frmt->arg[i--] = digit + '0';
			num /= 10;
			number_length--;
		}
		if (precision > 0)
			--precision;
	}
}

void			put_frmt_signed(t_ll num, t_format *frmt)
{
	size_t			index;
	size_t			numlen;

	numlen = ft_numlen(num);
	frmt->arg_index = get_total_len(num, frmt);
	if (frmt->flags.minus == 0)
	{
		frmt->arg = stralloc_and_fill(frmt->arg_index, (frmt->flags.minus == 0
					&& frmt->prec == 0 && frmt->flags.zero) ? '0' : ' ');
		ft_putnum(frmt, num, frmt->arg_index - 1, frmt->precision);
		index = 0;
		index += get_index(frmt->precision, numlen,
				frmt->arg_index - frmt->precision, frmt->arg_index - numlen);
		if (frmt->flags.zero == 1)
			ft_putsign(frmt, num, 0);
		else
			ft_putsign(frmt, num, index - 1);
	}
	else if (frmt->flags.minus == 1)
	{
		frmt->arg = stralloc_and_fill(frmt->arg_index, ' ');
		index = (ft_putsign(frmt, num, 0));
		index += get_index(frmt->precision, numlen, frmt->precision, numlen);
		ft_putnum(frmt, num, index - 1, frmt->precision);
	}
}
