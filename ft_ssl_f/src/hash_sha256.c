/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_sha256.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbovt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 18:19:33 by kbovt             #+#    #+#             */
/*   Updated: 2018/12/24 18:19:37 by kbovt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

const uint32_t	g_k2[] = {
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

void			calc_block_hash_sha256(t_ctx *ctx, void *block)
{
	uint32_t	*m;
	t_ctx		*tm_ctx;
	int			i;

	m = devide_block_sha256(block);
	add_words_sha256(m);
	tm_ctx = copy_ctx(ctx);
	i = -1;
	while (++i < 64)
		sha256_cycle(m, ctx, i);
	merge_ctx(ctx, tm_ctx);
	free(tm_ctx);
	free(m);
}

void			sha256_cycle(uint32_t *m, t_ctx *tm_ctx, int i)
{
	uint32_t e[2];
	uint32_t ma;
	uint32_t t1;
	uint32_t t2;
	uint32_t ch;

	e[0] = (ft_rotr(tm_ctx->h0, 2)) ^ \
	(ft_rotr(tm_ctx->h0, 13)) ^ (ft_rotr(tm_ctx->h0, 22));
	ma = (tm_ctx->h0 & tm_ctx->h1) ^ \
	(tm_ctx->h0 & tm_ctx->h2) ^ (tm_ctx->h1 & tm_ctx->h2);
	t2 = e[0] + ma;
	e[1] = (ft_rotr(tm_ctx->h4, 6)) ^ \
	(ft_rotr(tm_ctx->h4, 11)) ^ (ft_rotr(tm_ctx->h4, 25));
	ch = (tm_ctx->h4 & tm_ctx->h5) ^ ((~(tm_ctx->h4)) & tm_ctx->h6);
	t1 = tm_ctx->h7 + e[1] + ch + g_k2[i] + m[i];
	tm_ctx->h7 = tm_ctx->h6;
	tm_ctx->h6 = tm_ctx->h5;
	tm_ctx->h5 = tm_ctx->h4;
	tm_ctx->h4 = tm_ctx->h3 + t1;
	tm_ctx->h3 = tm_ctx->h2;
	tm_ctx->h2 = tm_ctx->h1;
	tm_ctx->h1 = tm_ctx->h0;
	tm_ctx->h0 = t1 + t2;
}

void			add_words_sha256(uint32_t *m)
{
	int			i;
	uint32_t	s0;
	uint32_t	s1;

	i = 15;
	while (++i < 64)
	{
		s0 = (ft_rotr(m[i - 15], 7)) ^ \
		(ft_rotr(m[i - 15], 18)) ^ (m[i - 15] >> 3);
		s1 = (ft_rotr(m[i - 2], 17)) ^ \
		(ft_rotr(m[i - 2], 19)) ^ (m[i - 2] >> 10);
		m[i] = m[i - 16] + s0 + m[i - 7] + s1;
	}
}

uint32_t		*devide_block_sha256(void *block)
{
	int			i;
	uint32_t	*new;
	uint32_t	*old;

	old = (uint32_t*)block;
	new = (uint32_t*)malloc(256);
	ft_bzero(new, 256);
	i = -1;
	while (++i < 16)
		ft_memcpy_rot(&(new[i]), &(old[i]), 4);
	return (new);
}

t_hash			*compile_hash_sha256(t_ctx *ctx)
{
	uint32_t	*temp;
	t_hash		*hash;

	temp = (uint32_t*)malloc(sizeof(uint32_t) * 8);
	temp[0] = ctx->h0;
	temp[1] = ctx->h1;
	temp[2] = ctx->h2;
	temp[3] = ctx->h3;
	temp[4] = ctx->h4;
	temp[5] = ctx->h5;
	temp[6] = ctx->h6;
	temp[7] = ctx->h7;
	hash = (t_hash*)malloc(sizeof(t_hash));
	hash->hash = temp;
	hash->len = 8;
	return (hash);
}
