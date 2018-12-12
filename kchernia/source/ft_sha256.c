/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 06:25:20 by kchernia          #+#    #+#             */
/*   Updated: 2018/10/19 09:00:00 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_sha256.h>

const uint32_t g_sha256_constants[] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static void	init_sha256_ctx(t_sha256_ctx *ctx, t_string msg)
{
	int				i;
	int16_t			step;
	uint64_t		len;

	step = 0;
	len = msg.len * 8;
	i = 1;
	while (i <= 8)
	{
		ctx->ctx[ctx->len - i] = (uint8_t)(len >> step);
		step += 8;
		i++;
	}
}

static void	init_sha256(t_string msg, t_sha256_ctx *ctx)
{
	ctx->state[0] = 0x6a09e667;
	ctx->state[1] = 0xbb67ae85;
	ctx->state[2] = 0x3c6ef372;
	ctx->state[3] = 0xa54ff53a;
	ctx->state[4] = 0x510e527f;
	ctx->state[5] = 0x9b05688c;
	ctx->state[6] = 0x1f83d9ab;
	ctx->state[7] = 0x5be0cd19;
	ctx->bitlen = (msg.len * 8) + 1;
	while (ctx->bitlen % 512 != 448)
		ctx->bitlen++;
	ctx->bitlen += 64;
	ctx->len = ctx->bitlen / 8;
	ctx->ctx = (uint8_t*)ft_strnew(ctx->len);
	ft_memchr(ctx->ctx, 0, ctx->len);
	ft_memcpy(ctx->ctx, msg.data, msg.len);
	ctx->ctx[msg.len] = (uint8_t)0x80;
	init_sha256_ctx(ctx, msg);
}

static char	*get_digest(t_sha256_ctx *ctx)
{
	uint32_t		i;
	uint32_t		j;
	char			*digest;

	digest = ft_strnew(64);
	ft_memchr(digest, 0, 64);
	i = 0;
	j = 0;
	while (i < 8)
	{
		ft_sprintf(digest + j, "%8.8x", ctx->state[i]);
		j += 8;
		++i;
	}
	return (digest);
}

char		*ft_sha256(t_string msg)
{
	char			*dgst;
	t_sha256_ctx	ctx;

	ctx.piece_cur = 0;
	init_sha256(msg, &ctx);
	while (ctx.piece_cur < ctx.len)
	{
		sha256_step_one(&ctx);
		sha256_step_two(&ctx);
		ctx.piece_cur += 64;
	}
	dgst = get_digest(&ctx);
	free(ctx.ctx);
	return (dgst);
}
