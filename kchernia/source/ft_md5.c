/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 18:13:31 by kchernia          #+#    #+#             */
/*   Updated: 2018/10/19 08:56:29 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_md5.h>

const uint32_t	g_md5_steps[] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

const uint32_t	g_md5_constants[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static void			init_md5_ctx(t_md5_ctx *ctx, t_string msg)
{
	int			i;
	int16_t		step;
	uint64_t	len;

	step = 0;
	len = msg.len * 8;
	i = 8;
	while (i > 0)
	{
		ctx->ctx[ctx->len - i] = (uint8_t)(len >> step);
		step += 8;
		i--;
	}
}

static void			init_md5(t_string msg, t_md5_ctx *ctx)
{
	ctx->state[0] = 0x67452301;
	ctx->state[1] = 0xefcdab89;
	ctx->state[2] = 0x98badcfe;
	ctx->state[3] = 0x10325476;
	ctx->bitlen = (msg.len * 8) + 1;
	while (ctx->bitlen % 512 != 448)
		ctx->bitlen++;
	ctx->bitlen += 64;
	ctx->len = ctx->bitlen / 8;
	ctx->ctx = (uint8_t*)ft_strnew(ctx->len);
	ft_memchr(ctx->ctx, 0, ctx->len);
	ft_memcpy(ctx->ctx, msg.data, msg.len);
	ctx->ctx[msg.len] = (uint8_t)0x80;
	init_md5_ctx(ctx, msg);
}

static char			*get_digest(t_md5_ctx *ctx)
{
	char		*digest;
	uint32_t	i;
	uint8_t		hash[16];

	i = 0;
	while (i < 4)
	{
		hash[i] = (uint8_t)((ctx->state[0] >> (i * 8)) & 0x000000ff);
		hash[i + 4] = (uint8_t)((ctx->state[1] >> (i * 8)) & 0x000000ff);
		hash[i + 8] = (uint8_t)((ctx->state[2] >> (i * 8)) & 0x000000ff);
		hash[i + 12] = (uint8_t)((ctx->state[3] >> (i * 8)) & 0x000000ff);
		++i;
	}
	digest = ft_strnew(32);
	ft_memchr(digest, 0, 32);
	i = 0;
	while (i < 16)
	{
		ft_sprintf(digest + (i * 2), "%2.2x", hash[i]);
		++i;
	}
	return (digest);
}

char				*ft_md5(t_string msg)
{
	char		*dgst;
	t_md5_ctx	ctx;

	ctx.piece_cur = 0;
	init_md5(msg, &ctx);
	while (ctx.piece_cur < ctx.len)
	{
		md5_step_one(&ctx);
		md5_step_two(&ctx);
		ctx.piece_cur += 64;
	}
	dgst = get_digest(&ctx);
	free(ctx.ctx);
	return (dgst);
}
