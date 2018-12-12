/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 16:03:38 by kchernia          #+#    #+#             */
/*   Updated: 2018/08/25 18:14:43 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void	get_char(va_list *ap, t_format *frmt)
{
	wint_t c;

	if (frmt->type == 'c' && frmt->size == MDF_L)
		frmt->type = 'C';
	if (frmt->type == 'C')
		c = (wchar_t)va_arg(*ap, wint_t);
	else
		c = (signed char)va_arg(*ap, int);
	put_frmt_char((void*)&c, frmt);
}

static void	get_str(va_list *ap, t_format *frmt)
{
	wchar_t	*ws;
	char	*s;

	if (frmt->type == 's' && frmt->size == MDF_L)
		frmt->type = 'S';
	if (frmt->type == 'S')
	{
		ws = va_arg(*ap, wchar_t*);
		if (!ws)
			ws = L"(null)";
		put_frmt_str((void*)ws, frmt);
	}
	else
	{
		s = va_arg(*ap, char*);
		if (!s)
			s = "(null)";
		put_frmt_str((void*)s, frmt);
	}
}

static void	get_signed(va_list *ap, t_format *frmt)
{
	long long int	n;

	if (frmt->size == MDF_HH)
		n = (signed char)va_arg(*ap, int);
	else if (frmt->size == MDF_H)
		n = (short)va_arg(*ap, int);
	else if (frmt->size == MDF_L)
		n = (long)va_arg(*ap, long);
	else if (frmt->size == MDF_LL || frmt->size == MDF_J ||
			frmt->size == MDF_Z)
		n = (long long)va_arg(*ap, long long);
	else
		n = (int)va_arg(*ap, int);
	put_frmt_signed(n, frmt);
}

static void	get_unsigned(va_list *ap, t_format *frmt)
{
	unsigned long long int	n;

	if (frmt->size == MDF_HH)
		n = (unsigned char)va_arg(*ap, unsigned int);
	else if (frmt->size == MDF_H)
		n = (unsigned short)va_arg(*ap, unsigned int);
	else if (frmt->size == MDF_L)
		n = (unsigned long)va_arg(*ap, unsigned long);
	else if (frmt->size == MDF_LL || frmt->size == MDF_J ||
			frmt->size == MDF_Z)
		n = (unsigned long long)va_arg(*ap, unsigned long long);
	else
		n = (unsigned int)va_arg(*ap, unsigned int);
	put_frmt_unsigned(n, frmt);
}

void		get_arg(va_list *ap, t_format *frmt)
{
	char	c;
	void	*ptr;

	c = frmt->type;
	if (IS_CHAR(c))
		get_char(ap, frmt);
	else if (IS_STRING(c))
		get_str(ap, frmt);
	else if (IS_SIGNED_INT(c))
		get_signed(ap, frmt);
	else if (IS_UINT(c))
		get_unsigned(ap, frmt);
	else if (IS_POINTER(c))
	{
		ptr = (void*)va_arg(*ap, void*);
		put_frmt_pointer((void*)ptr, frmt);
	}
	else if (IS_PERCENT(c))
		put_frmt_percent(frmt);
}
