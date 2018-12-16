/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbovt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 13:34:57 by kbovt             #+#    #+#             */
/*   Updated: 2018/12/15 13:35:47 by kbovt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_print_memory(void *ptr, int length, char *flags)
{
	int				i;
	unsigned char	c;
	unsigned char	*p;

	p = (unsigned char*)ptr;
	i = 0;
	while (i < length)
	{
		c = p[i];
		ft_print_byte(c);
		write(1, " | ", 3);
		if (ft_strchr(flags, (int)'d'))
		{
			ft_putnbr((int)c);
			write(1, " | ", 3);
		}
		if (ft_strchr(flags, (int)'c'))
		{
			ft_putnbr(i);
			write(1, "\n", 1);
		}
		i++;
	}
	write(1, "\n", 1);
}
