/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_signed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:38:56 by kchernia          #+#    #+#             */
/*   Updated: 2018/08/25 18:17:34 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int		ft_putsign(t_format *frmt, t_ll num, size_t i)
{
	if (num < 0)
		frmt->arg[i] = '-';
	else if ((frmt->flags.plus == 1 || frmt->flags.space == 1) && num >= 0)
	{
		frmt->arg[i] = (frmt->flags.plus == 1) ? '+' : ' ';
		i++;
	}
	else
		return (0);
	return (1);
}

size_t	get_index(size_t c1, size_t c2, size_t r1, size_t r2)
{
	if (c1 > c2)
		return (r1);
	else
		return (r2);
}
