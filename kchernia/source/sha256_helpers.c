/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 08:58:55 by kchernia          #+#    #+#             */
/*   Updated: 2018/10/19 09:01:38 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sha256.h>

static void	sha256_step_one_p2(t_sha256_ctx *ctx, uint64_t i)
{
	uint32_t		s0;
	uint32_t		s1;

	while (i < 64)
	{
		s0 = S256_RR(ctx->piece[i - 15], 7) ^ S256_RR(ctx->piece[i - 15], 18) ^
			(ctx->piece[i - 15] >> 3);
		s1 = S256_RR(ctx->piece[i - 2], 17) ^ S256_RR(ctx->piece[i - 2], 19) ^
			(ctx->piece[i - 2] >> 10);
		ctx->piece[i] = ctx->piece[i - 16] + s0 + ctx->piece[i - 7] + s1;
		++i;
	}
	ft_memcpy(ctx->tmp, ctx->state, sizeof(uint32_t) * 8);
}

void		sha256_step_one(t_sha256_ctx *ctx)
{
	uint8_t			*ptr;
	uint64_t		i;
	uint64_t		j;

	ft_memset(ctx->piece, 0, sizeof(uint32_t) * 64);
	ptr = ctx->ctx + ctx->piece_cur;
	i = 0;
	j = 0;
	while (i < 16)
	{
		ctx->piece[i] = (ptr[j] << 24) | (ptr[j + 1] << 16) |
						(ptr[j + 2] << 8) | (ptr[j + 3]);
		j += 4;
		i++;
	}
	sha256_step_one_p2(ctx, i);
}

static void	sha256_step_two_cp(t_sha256_ctx *ctx, uint32_t tmp1,
								uint32_t tmp2)
{
	int64_t			i;

	i = 7;
	while (i >= 0)
	{
		if (i != 4 && i != 0)
			ctx->tmp[i] = ctx->tmp[i - 1];
		else if (i == 4)
			ctx->tmp[i] = ctx->tmp[i - 1] + tmp1;
		else
			ctx->tmp[i] = tmp1 + tmp2;
		--i;
	}
}

void		sha256_step_two(t_sha256_ctx *ctx)
{
	int64_t			i;
	uint32_t		tmp1;
	uint32_t		tmp2;

	i = 0;
	while (i < 64)
	{
		tmp1 = ctx->tmp[7] + S256_S1(ctx->tmp[4]) + S256_CH(ctx->tmp[4],
				ctx->tmp[5], ctx->tmp[6]) + g_sha256_constants[i] +
				ctx->piece[i];
		tmp2 = S256_S0(ctx->tmp[0]) + S256_MAJ(ctx->tmp[0], ctx->tmp[1],
				ctx->tmp[2]);
		sha256_step_two_cp(ctx, tmp1, tmp2);
		++i;
	}
	i = 0;
	while (i < 8)
	{
		ctx->state[i] += ctx->tmp[i];
		++i;
	}
}
