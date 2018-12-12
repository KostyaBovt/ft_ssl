/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 08:55:11 by kchernia          #+#    #+#             */
/*   Updated: 2018/10/19 08:56:58 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_md5.h>

void				md5_step_one(t_md5_ctx *ctx)
{
	uint8_t		*ptr;
	uint64_t	i;
	uint64_t	j;

	ptr = ctx->ctx + ctx->piece_cur;
	i = 0;
	j = 0;
	while (i < 16)
	{
		ctx->piece[i] = (ptr[j]) + (ptr[j + 1] << 8) +
						(ptr[j + 2] << 16) + (ptr[j + 3] << 24);
		j += 4;
		i++;
	}
	ft_memcpy(ctx->tmp, ctx->state, sizeof(uint32_t) * 4);
}

static void			md5_handle_four_steps(t_md5_ctx *ctx, uint32_t *tmp1,
										uint32_t *tmp2, uint32_t i)
{
	if (i < 16)
	{
		FF_FUNC(ctx->tmp[1], ctx->tmp[2], ctx->tmp[3], *tmp1, *tmp2, i);
	}
	else if (i >= 16 && i < 32)
	{
		GG_FUNC(ctx->tmp[1], ctx->tmp[2], ctx->tmp[3], *tmp1, *tmp2, i);
	}
	else if (i >= 32 && i < 48)
	{
		HH_FUNC(ctx->tmp[1], ctx->tmp[2], ctx->tmp[3], *tmp1, *tmp2, i);
	}
	else
	{
		II_FUNC(ctx->tmp[1], ctx->tmp[2], ctx->tmp[3], *tmp1, *tmp2, i);
	}
	*tmp1 = *tmp1 + ctx->tmp[0] + g_md5_constants[i] + ctx->piece[*tmp2];
	ctx->tmp[0] = ctx->tmp[3];
	ctx->tmp[3] = ctx->tmp[2];
	ctx->tmp[2] = ctx->tmp[1];
	ctx->tmp[1] += MD5_LR(*tmp1, g_md5_steps[i]);
}

void				md5_step_two(t_md5_ctx *ctx)
{
	uint32_t	i;
	uint32_t	tmp1;
	uint32_t	tmp2;

	i = 0;
	while (i < 64)
	{
		md5_handle_four_steps(ctx, &tmp1, &tmp2, i);
		++i;
	}
	i = 0;
	while (i < 4)
	{
		ctx->state[i] += ctx->tmp[i];
		++i;
	}
}
