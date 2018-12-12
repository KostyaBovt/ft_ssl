/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 21:04:59 by kchernia          #+#    #+#             */
/*   Updated: 2018/08/25 20:37:05 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void	check_width(t_format *frmt, va_list *ap)
{
	long int	width;

	width = (long long int)va_arg(*ap, int);
	if (width < 0)
	{
		frmt->flags.minus = 1;
		width = width * -1;
	}
	frmt->width = width;
}

static void	check_prec(t_format *frmt, va_list *ap)
{
	long int	prec;

	prec = (long long int)va_arg(*ap, int);
	if (prec < 0)
	{
		frmt->prec = 0;
		frmt->precision = 0;
	}
	else
		frmt->precision = prec;
}

static void	get_star(const char **cur, t_format *frmt,
					int is_width, va_list *ap)
{
	if (**cur == '*')
	{
		++*cur;
		if (is_width)
			check_width(frmt, ap);
		else
			check_prec(frmt, ap);
	}
	else
		check_digit((is_width ? (&frmt->width) : (&frmt->precision)), cur);
}

int			get_format(const char **start, const char **cur,
						t_format *frmt, va_list *ap)
{
	check_flags(cur, frmt);
	get_star(cur, frmt, 1, ap);
	if (**cur == '.')
	{
		(*cur)++;
		frmt->prec = 1;
		get_star(cur, frmt, 0, ap);
	}
	check_size(cur, frmt);
	if (IS_TYPE(**cur))
	{
		if (**cur != 'X' && (**cur >= 'A' && **cur <= 'Z'))
			frmt->size = MDF_L;
		frmt->type = **cur;
		(*cur)++;
		return (1);
	}
	add_to_result(frmt, *start, *cur - *start);
	return (0);
}
