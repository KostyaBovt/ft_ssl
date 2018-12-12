/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 19:58:13 by kchernia          #+#    #+#             */
/*   Updated: 2018/08/25 21:20:19 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

char		*stralloc_and_fill(size_t size, char c)
{
	size_t	i;
	char	*new_str;

	new_str = malloc(sizeof(char) * (size + 1));
	i = 0;
	while (i < size)
		new_str[i++] = c;
	new_str[i] = 0;
	return (new_str);
}

static char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

static char	*ft_realloc(char *dst, int size, int new_size)
{
	char	*tmp;
	int		i;

	tmp = (char*)malloc(sizeof(char) * new_size);
	i = 0;
	while (i < size)
	{
		tmp[i] = dst[i];
		i++;
	}
	while (i < new_size)
		tmp[i++] = 0;
	free(dst);
	return (tmp);
}

void		add_to_result(t_format *frmt, const char *src, size_t n)
{
	if (frmt->result_size - frmt->result_index < n)
	{
		frmt->result = ft_realloc(frmt->result, frmt->result_size,
			(frmt->result_size * 2) + n);
		frmt->result_size = (frmt->result_size * 2) + n;
	}
	ft_strncpy(frmt->result + frmt->result_index, src, n);
	frmt->result_index += n;
}
