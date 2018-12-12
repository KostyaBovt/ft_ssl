/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 20:21:22 by kchernia          #+#    #+#             */
/*   Updated: 2018/08/25 21:29:01 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

void	clean_format(t_format *frmt)
{
	if (!frmt->result)
	{
		frmt->result_size = 100;
		frmt->result_index = 0;
		frmt->result = (char*)malloc(sizeof(char) * frmt->result_size);
	}
	frmt->flags.hash = 0;
	frmt->flags.minus = 0;
	frmt->flags.plus = 0;
	frmt->flags.space = 0;
	frmt->flags.zero = 0;
	frmt->width = 0;
	frmt->precision = 0;
	frmt->prec = 0;
	frmt->size = 0;
	frmt->type = 0;
	frmt->arg = 0;
	frmt->arg_index = 0;
	frmt->is_ptr = 0;
}

void	check_flags(const char **cur, t_format *frmt)
{
	while (IS_FLAG(**cur))
	{
		if (**cur == '#')
			frmt->flags.hash = 1;
		else if (**cur == '0')
			frmt->flags.zero = 1;
		else if (**cur == '-')
			frmt->flags.minus = 1;
		else if (**cur == '+')
			frmt->flags.plus = 1;
		else if (**cur == ' ')
			frmt->flags.space = 1;
		(*cur)++;
	}
}

void	check_digit(size_t *dst, const char **cur)
{
	while (IS_DIGIT(**cur))
	{
		*dst = *dst * 10 + (**cur - '0');
		(*cur)++;
	}
}

void	move_if(int if_result, int *assign_if, int assign_value,
						char const **to_move)
{
	if (if_result)
	{
		*assign_if = assign_value;
		++*to_move;
	}
}

void	check_size(const char **cur, t_format *frmt)
{
	while (IS_SIZE(**cur))
	{
		if (**cur == 'h')
		{
			frmt->size = MDF_H;
			move_if((*(*cur + 1) == 'h'), &frmt->size, MDF_HH, cur);
		}
		else if (**cur == 'l')
		{
			frmt->size = MDF_L;
			move_if((*(*cur + 1) == 'l'), &frmt->size, MDF_LL, cur);
		}
		else if (**cur == 'j')
			frmt->size = MDF_J;
		else if (**cur == 'z')
			frmt->size = MDF_Z;
		(*cur)++;
	}
}
