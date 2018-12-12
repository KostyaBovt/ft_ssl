/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_frmt_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 17:59:13 by kchernia          #+#    #+#             */
/*   Updated: 2018/08/25 15:07:50 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

size_t	wchar_size(wchar_t c)
{
	if (c <= 0x7F)
		return (1);
	else if (c <= 0x7FF)
		return (2);
	else if (c <= 0xFFFF)
		return (3);
	else
		return (4);
}

size_t	widestrtostrlen(wchar_t const *str, size_t precision)
{
	size_t	i;
	size_t	len;
	size_t	wc_width;

	i = 0;
	len = 0;
	while (str[i])
	{
		wc_width = wchar_size(str[i]);
		if (precision > 0 && precision - len < wc_width)
			break ;
		len += wc_width;
		++i;
	}
	return (len);
}

void	write_wsize_chars(char *s, size_t i, size_t wsize, wchar_t c)
{
	if (wsize == 2)
	{
		s[i++] = (char)((c >> 6) + 0xC0);
		s[i++] = (char)((c & 0x3F) + 0x80);
	}
	else if (wsize == 3)
	{
		s[i++] = (char)((c >> 12) + 0xE0);
		s[i++] = (char)(((c >> 6) & 0x3F) + 0x80);
		s[i++] = (char)((c & 0x3F) + 0x80);
	}
	else
	{
		s[i++] = (char)((c >> 18) + 0xF0);
		s[i++] = (char)(((c >> 12) & 0x3F) + 0x80);
		s[i++] = (char)(((c >> 6) & 0x3F) + 0x80);
		s[i++] = (char)((c & 0x3F) + 0x80);
	}
}

void	widestrtostrn(wchar_t const *ws, char *s, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	wsize;

	i = 0;
	j = 0;
	while (i < n)
	{
		wsize = wchar_size(ws[j]);
		if (i + wsize > n)
			break ;
		if (wsize == 1)
			s[i] = (char)ws[j];
		else
			write_wsize_chars(s, i, wsize, ws[j]);
		i += wsize;
		++j;
	}
}

void	put_frmt_str(void *input, t_format *frmt)
{
	int		need_free;
	size_t	len;
	wchar_t	*tmp;

	if ((need_free = 0) == 0 && frmt->type == 's')
	{
		len = ft_strlen((char*)input);
		tmp = wstrnew(len, L' ');
		strtowidestrn((char*)input, tmp, len);
		input = (void*)tmp;
		need_free = 1;
	}
	len = widestrtostrlen((wchar_t*)input, frmt->precision);
	if (frmt->prec && len > frmt->precision)
		len = frmt->precision;
	frmt->arg_index = (frmt->width < len) ? len : frmt->width;
	frmt->arg = stralloc_and_fill(frmt->arg_index,
				((frmt->flags.zero) ? '0' : ' '));
	if (frmt->flags.minus)
		widestrtostrn((wchar_t*)input, frmt->arg, len);
	else
		widestrtostrn((wchar_t*)input,
					(frmt->arg + frmt->arg_index - len), len);
	if (need_free)
		free(input);
}
