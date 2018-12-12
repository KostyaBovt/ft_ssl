/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 08:32:08 by kchernia          #+#    #+#             */
/*   Updated: 2018/10/19 08:36:52 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>
#include <libft.h>

int	ft_sprintf(char *str, const char *format, ...)
{
	va_list		ap;
	char		*res;
	int			ret;

	va_start(ap, format);
	ret = ft_vsprintf(&res, format, &ap);
	if (ret > 0)
		ft_strncpy(str, res, (size_t)ret);
	free(res);
	va_end(ap);
	return (ret);
}
