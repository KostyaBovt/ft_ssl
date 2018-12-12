/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 19:51:50 by kchernia          #+#    #+#             */
/*   Updated: 2018/10/19 08:51:57 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <libft.h>

int				ft_printf(const char *format, ...)
{
	va_list		ap;
	char		*res;
	int			ret;

	va_start(ap, format);
	ret = ft_vsprintf(&res, format, &ap);
	if (ret > 0)
		write(STDOUT_FILENO, res, (size_t)ret);
	free(res);
	va_end(ap);
	return (ret);
}
