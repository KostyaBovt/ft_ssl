/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_widestring.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 16:18:32 by kchernia          #+#    #+#             */
/*   Updated: 2018/09/11 20:20:47 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

wchar_t	*wstrnew(size_t size, wchar_t c)
{
	size_t	i;
	wchar_t	*new_str;

	i = 0;
	new_str = malloc(sizeof(wchar_t) * (size + 1));
	while (i < size)
		new_str[i++] = c;
	new_str[i] = 0;
	return (new_str);
}

void	strtowidestrn(char const *s, wchar_t *ws, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		ws[i] = (wchar_t)s[i];
		++i;
	}
}
