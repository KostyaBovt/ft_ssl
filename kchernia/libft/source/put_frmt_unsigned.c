/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_frmt_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 18:22:07 by kchernia          #+#    #+#             */
/*   Updated: 2018/08/25 19:57:12 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	ft_putoxnum(t_format *frmt, t_ull num, int i, size_t numlen)
{
	char const	*tab;
	size_t		precision;
	int			base;

	precision = frmt->precision;
	get_base_tab(frmt, &tab, &base);
	if (frmt->prec && precision == 0 && num == 0 && !frmt->flags.hash)
		numlen = 0;
	while (numlen > 0 || precision > 0)
	{
		if (numlen == 0 && precision > 0)
			frmt->arg[i--] = '0';
		else
		{
			frmt->arg[i--] = tab[num % base];
			num /= base;
			numlen--;
		}
		if (precision > 0)
			--precision;
	}
}

void	put_frmt_ui(t_ull num, t_format *frmt)
{
	int				index;
	size_t			numlen;

	numlen = unumlen_base(num, 10);
	frmt->arg_index = get_total_len_ui(num, frmt, numlen);
	if (frmt->flags.minus == 0)
	{
		frmt->arg = stralloc_and_fill(frmt->arg_index, (frmt->flags.minus == 0
					&& frmt->prec == 0 && frmt->flags.zero) ? '0' : ' ');
		ft_putunum(frmt, num, frmt->arg_index - 1);
	}
	else if (frmt->flags.minus == 1)
	{
		frmt->arg = stralloc_and_fill(frmt->arg_index, ' ');
		index = 0;
		index += (frmt->precision > numlen) ? frmt->precision : numlen;
		ft_putunum(frmt, num, index - 1);
	}
}

void	put_frmt_ux(t_ull num, t_format *frmt, int base)
{
	size_t	index;
	size_t	numlen;

	numlen = unumlen_base(num, base);
	frmt->arg_index = get_total_len_ux(num, frmt, &numlen);
	index = 0;
	if (frmt->flags.minus == 0)
	{
		frmt->arg = stralloc_and_fill(frmt->arg_index, (frmt->flags.minus == 0
					&& frmt->prec == 0 && frmt->flags.zero) ? '0' : ' ');
		ft_putoxnum(frmt, num, frmt->arg_index - 1, numlen);
		index += get_index(frmt->precision, numlen, frmt->arg_index -
					frmt->precision - 1, frmt->arg_index - numlen - 1);
		if (frmt->flags.hash == 1 && (num != 0 || frmt->is_ptr))
			get_alter_form(frmt, index, 1);
	}
	else if (frmt->flags.minus == 1)
	{
		frmt->arg = stralloc_and_fill(frmt->arg_index, ' ');
		if (frmt->flags.hash == 1 && (num != 0 || frmt->is_ptr))
			index += ft_put_alter_form(frmt, 1);
		index += get_index(frmt->precision, numlen,
						frmt->precision - 1, numlen - 1);
		ft_putoxnum(frmt, num, index, numlen);
	}
}

void	put_frmt_uo(t_ull num, t_format *frmt)
{
	size_t	index;
	size_t	numlen;

	numlen = unumlen_base(num, 8);
	frmt->arg_index = get_total_len_uo(num, frmt, numlen);
	index = 0;
	if (frmt->flags.minus == 0)
	{
		frmt->arg = stralloc_and_fill(frmt->arg_index, (frmt->flags.minus == 0
					&& frmt->prec == 0 && frmt->flags.zero) ? '0' : ' ');
		ft_putoxnum(frmt, num, frmt->arg_index - 1, numlen);
		index += get_index(frmt->precision, numlen, frmt->arg_index -
						frmt->precision - 1, frmt->arg_index - numlen - 1);
		if (num != 0 && frmt->flags.hash == 1)
			get_alter_form(frmt, index, 0);
	}
	else if (frmt->flags.minus == 1)
	{
		frmt->arg = stralloc_and_fill(frmt->arg_index, ' ');
		if (num != 0 && frmt->flags.hash == 1)
			index += ft_put_alter_form(frmt, 0);
		index += get_index(frmt->precision, numlen,
						frmt->precision - 1, numlen - 1);
		ft_putoxnum(frmt, num, index, numlen);
	}
}

void	put_frmt_unsigned(t_ull num, t_format *frmt)
{
	if (TO_INT(frmt->type))
		put_frmt_ui(num, frmt);
	else if (TO_HEX(frmt->type))
		put_frmt_ux(num, frmt, 16);
	else if (TO_OCT(frmt->type))
		put_frmt_uo(num, frmt);
	else if (TO_BINARY(frmt->type))
		put_frmt_ux(num, frmt, 2);
}
