/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 04:19:12 by kchernia          #+#    #+#             */
/*   Updated: 2018/10/19 06:44:06 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHA256_H
# define FT_SHA256_H

# include <libft.h>

# define S256_RR(X, Y) (((X) >> (Y)) | ((X) << (32 - (Y))))

# define S256_S0(A) (S256_RR((A), 2) ^ S256_RR((A), 13) ^ S256_RR((A), 22))
# define S256_S1(E) (S256_RR((E), 6) ^ S256_RR((E), 11) ^ S256_RR((E), 25))
# define S256_CH(E, F, G) (((E) & (F)) ^ ((~(E)) & (G)))
# define S256_MAJ(A, B, C) (((A) & (B)) ^ ((A) & (C)) ^ ((B) & (C)))

extern const uint32_t	g_sha256_constants[];

typedef struct			s_sha256_ctx
{
	uint8_t				*ctx;
	uint64_t			len;
	uint64_t			bitlen;
	uint32_t			state[8];
	uint32_t			tmp[8];
	uint64_t			piece_cur;
	uint32_t			piece[64];
}						t_sha256_ctx;

char					*ft_sha256(t_string msg);
void					sha256_step_one(t_sha256_ctx *ctx);
void					sha256_step_two(t_sha256_ctx *ctx);

#endif
