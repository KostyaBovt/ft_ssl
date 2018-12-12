/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_frmt_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 18:21:11 by kchernia          #+#    #+#             */
/*   Updated: 2018/08/25 19:57:47 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	put_frmt_pointer(void *input, t_format *frmt)
{
	unsigned long long	x;

	frmt->type = 'x';
	frmt->is_ptr = 1;
	frmt->flags.hash = 1;
	if (!input && frmt->width < 3)
		frmt->width = 3;
	x = (unsigned long long)input;
	put_frmt_ux(x, frmt, 16);
}
