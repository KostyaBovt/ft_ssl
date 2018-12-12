/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 04:19:46 by kchernia          #+#    #+#             */
/*   Updated: 2018/10/19 08:57:26 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

# include <libft.h>

# define MD5_LR(A, B) (((A) << (B)) | ((A) >> (32 - (B))))

# define F_FUNC(B, C, D) ((B & C) | ((~B) & D))
# define FF_FUNC(B, C, D, F, G, I) F = F_FUNC(B, C, D); G = I
# define G_FUNC(B, C, D) ((D & B) | ((~D) & C))
# define GG_FUNC(B, C, D, F, G, I) F = G_FUNC(B, C, D); G = (5 * I + 1) % 16
# define H_FUNC(B, C, D) (B ^ C ^ D)
# define HH_FUNC(B, C, D, F, G, I) F = H_FUNC(B, C, D); G = (3 * I + 5) % 16
# define I_FUNC(B, C, D) (C ^ (B | (~D)))
# define II_FUNC(B, C, D, F, G, I) F = I_FUNC(B, C, D); G = (7 * I) % 16

extern const uint32_t	g_md5_steps[];
extern const uint32_t	g_md5_constants[];

typedef struct			s_md5_ctx
{
	uint8_t				*ctx;
	uint64_t			len;
	uint64_t			bitlen;
	uint32_t			state[4];
	uint32_t			tmp[4];
	uint64_t			piece_cur;
	uint32_t			piece[16];
}						t_md5_ctx;

char					*ft_md5(t_string msg);
void					md5_step_one(t_md5_ctx *ctx);
void					md5_step_two(t_md5_ctx *ctx);

#endif
