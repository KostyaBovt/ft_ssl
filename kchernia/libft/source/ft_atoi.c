/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 03:33:55 by kchernia          #+#    #+#             */
/*   Updated: 2018/01/25 16:38:32 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long	num;
	int			sign;

	num = 0;
	while ((*str >= '\t' && *str <= '\r') || *str == ' ')
		++str;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		sign = *str == '-' ? -1 : 1;
		++str;
	}
	while (*str >= '0' && *str <= '9')
	{
		if ((num > 922337203685477580 || (num == 922337203685477580
			&& (*str - '0') > 7)) && sign == 1)
			return (-1);
		else if ((num > 922337203685477580 || (num == 922337203685477580
				&& (*str - '0') > 8)) && sign == -1)
			return (0);
		num = num * 10 + (*str - '0');
		++str;
	}
	return (num * sign);
}