/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vsprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 08:31:25 by kchernia          #+#    #+#             */
/*   Updated: 2018/10/19 08:40:04 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void		add_last(t_format *frmt, const char *start, const char *format,
				char **strp)
{
	add_to_result(frmt, start, format - start);
	*strp = frmt->result;
}

static void		add_arg(t_format *frmt, va_list *ap)
{
	get_arg(ap, frmt);
	if (frmt->arg_index > 0 && frmt->arg)
	{
		add_to_result(frmt, frmt->arg, frmt->arg_index);
		free(frmt->arg);
	}
	clean_format(frmt);
}

static void		init_printf(t_format *frmt, const char **start,
				const char **format)
{
	*start = *format;
	frmt->result = 0;
	clean_format(frmt);
}

int				ft_vsprintf(char **strp, const char *format, va_list *ap)
{
	const char	*start;
	t_format	frmt;

	if (!format)
		return (-1);
	init_printf(&frmt, &start, &format);
	while (*format != 0)
	{
		if (*format == '%')
		{
			add_to_result(&frmt, start, format++ - start);
			if (get_format(&start, &format, &frmt, ap))
				add_arg(&frmt, ap);
			start = format;
		}
		else
			format++;
	}
	add_last(&frmt, start, format, strp);
	return ((int)frmt.result_index);
}
