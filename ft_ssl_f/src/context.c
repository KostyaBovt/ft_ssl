/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbovt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 18:18:22 by kbovt             #+#    #+#             */
/*   Updated: 2018/12/24 18:18:25 by kbovt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

t_ctx	*init_ctx(void)
{
	t_ctx	*new;

	new = (t_ctx*)malloc(sizeof(t_ctx));
	new->a = 0x67452301;
	new->b = 0xefcdab89;
	new->c = 0x98badcfe;
	new->d = 0x10325476;
	new->h0 = 0x6A09E667;
	new->h1 = 0xBB67AE85;
	new->h2 = 0x3C6EF372;
	new->h3 = 0xA54FF53A;
	new->h4 = 0x510E527F;
	new->h5 = 0x9B05688C;
	new->h6 = 0x1F83D9AB;
	new->h7 = 0x5BE0CD19;
	return (new);
}

t_ctx	*copy_ctx(t_ctx *ctx)
{
	t_ctx	*new;

	new = (t_ctx*)malloc(sizeof(t_ctx));
	new->a = ctx->a;
	new->b = ctx->b;
	new->c = ctx->c;
	new->d = ctx->d;
	new->h0 = ctx->h0;
	new->h1 = ctx->h1;
	new->h2 = ctx->h2;
	new->h3 = ctx->h3;
	new->h4 = ctx->h4;
	new->h5 = ctx->h5;
	new->h6 = ctx->h6;
	new->h7 = ctx->h7;
	return (new);
}

void	print_ctx(t_ctx *ctx)
{
	ft_printf("A: %zu\n", ctx->a);
	ft_printf("B: %zu\n", ctx->b);
	ft_printf("C: %zu\n", ctx->c);
	ft_printf("D: %zu\n", ctx->d);
	ft_printf("h0 (a): %zu\n", ctx->h0);
	ft_printf("h1 (b): %zu\n", ctx->h1);
	ft_printf("h2 (c): %zu\n", ctx->h2);
	ft_printf("h3 (d): %zu\n", ctx->h3);
	ft_printf("h4 (e): %zu\n", ctx->h4);
	ft_printf("h5 (f): %zu\n", ctx->h5);
	ft_printf("h6 (g): %zu\n", ctx->h6);
	ft_printf("h7 (h): %zu\n", ctx->h7);
}

void	print_ctx_hex(t_ctx *ctx)
{
	ft_printf("A: %X\n", ctx->a);
	ft_printf("B: %X\n", ctx->b);
	ft_printf("C: %X\n", ctx->c);
	ft_printf("D: %X\n", ctx->d);
	ft_printf("h0 (a): %X\n", ctx->h0);
	ft_printf("h1 (b): %X\n", ctx->h1);
	ft_printf("h2 (c): %X\n", ctx->h2);
	ft_printf("h3 (d): %X\n", ctx->h3);
	ft_printf("h4 (e): %X\n", ctx->h4);
	ft_printf("h5 (f): %X\n", ctx->h5);
	ft_printf("h6 (g): %X\n", ctx->h6);
	ft_printf("h7 (h): %X\n", ctx->h7);
}

void	merge_ctx(t_ctx *ctx, t_ctx *temp_ctx)
{
	ctx->a += temp_ctx->a;
	ctx->b += temp_ctx->b;
	ctx->c += temp_ctx->c;
	ctx->d += temp_ctx->d;
	ctx->h0 += temp_ctx->h0;
	ctx->h1 += temp_ctx->h1;
	ctx->h2 += temp_ctx->h2;
	ctx->h3 += temp_ctx->h3;
	ctx->h4 += temp_ctx->h4;
	ctx->h5 += temp_ctx->h5;
	ctx->h6 += temp_ctx->h6;
	ctx->h7 += temp_ctx->h7;
}
