/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:41:19 by kchernia          #+#    #+#             */
/*   Updated: 2018/08/25 20:00:45 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	get_base_tab(t_format *frmt, char const **tab, int *base)
{
	if (TO_OCT(frmt->type))
	{
		*tab = "01234567";
		*base = 8;
	}
	else if (TO_HEX(frmt->type))
	{
		*tab = (frmt->type == 'X') ? ("0123456789ABCDEF")
		: ("0123456789abcdef");
		*base = 16;
	}
	else if (TO_BINARY(frmt->type))
	{
		*tab = "01";
		*base = 2;
	}
}

size_t	unumlen_base(t_ull number, int base)
{
	size_t	len;

	if ((len = 0) == 0 && number == 0)
		return (1);
	while (number)
	{
		number /= base;
		++len;
	}
	return (len);
}

size_t	get_total_len_ui(t_ull num, t_format *frmt, size_t numlen)
{
	size_t	len;

	len = numlen;
	if (frmt->precision > len)
		len = frmt->precision;
	if (frmt->width > len || (frmt->prec && frmt->precision == 0 && num == 0))
		len = frmt->width;
	return (len);
}

void	ft_putunum(t_format *frmt, t_ull num, int i)
{
	size_t	number_length;

	number_length = unumlen_base(num, 10);
	if (frmt->prec && frmt->precision == 0 && num == 0)
		number_length = 0;
	while (number_length > 0 || frmt->precision > 0)
	{
		if (number_length == 0 && frmt->precision > 0)
			frmt->arg[i--] = '0';
		else
		{
			frmt->arg[i--] = (num % 10) + '0';
			num /= 10;
			number_length--;
		}
		if (frmt->precision > 0)
			--frmt->precision;
	}
}
