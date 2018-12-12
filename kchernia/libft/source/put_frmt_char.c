/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_frmt_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 18:20:37 by kchernia          #+#    #+#             */
/*   Updated: 2018/08/25 21:21:11 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	put_frmt_char(void *input, t_format *frmt)
{
	size_t	len;
	wchar_t	tmp;

	if (frmt->type == 'c')
		tmp = (wchar_t)*((char*)input);
	else
		tmp = *((wchar_t*)input);
	len = wchar_size(tmp);
	frmt->arg_index = frmt->width;
	frmt->arg_index = (frmt->arg_index < len) ? len : frmt->arg_index;
	frmt->arg = stralloc_and_fill(frmt->arg_index,
				((frmt->flags.zero) ? '0' : ' '));
	if (frmt->flags.minus)
		widestrtostrn(&tmp, frmt->arg, len);
	else
		widestrtostrn(&tmp, frmt->arg + frmt->arg_index - len, len);
}

void	put_frmt_percent(t_format *frmt)
{
	size_t		width;

	width = 1;
	if (frmt->width > width)
		width = frmt->width;
	frmt->arg_index = width;
	if (frmt->flags.minus == 0)
		frmt->arg = stralloc_and_fill(width, ((frmt->flags.zero) ? '0' : ' '));
	else if (frmt->flags.minus == 1)
		frmt->arg = stralloc_and_fill(width, ' ');
	if (frmt->flags.minus)
		frmt->arg[0] = '%';
	else
		frmt->arg[width - 1] = '%';
}
