/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbovt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 22:39:54 by kbovt             #+#    #+#             */
/*   Updated: 2018/12/24 22:39:56 by kbovt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void			print_block_sha256(uint32_t *block)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (i < 64)
	{
		ft_printf("word [%d]: %X | ", i, block[i]);
		len = sizeof(*block);
		j = -1;
		while (++j < len)
			ft_print_byte(((unsigned char *)(&block[i]))[j]);
		ft_printf("\n");
		i++;
	}
}
