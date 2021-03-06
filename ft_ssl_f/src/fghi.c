/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fghi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbovt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 18:18:33 by kbovt             #+#    #+#             */
/*   Updated: 2018/12/24 18:18:35 by kbovt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

uint32_t	md5_f(t_ctx *ctx)
{
	uint32_t	ret;

	ret = ((ctx->b & ctx->c) | (~(ctx->b) & ctx->d));
	return (ret);
}

uint32_t	md5_g(t_ctx *ctx)
{
	return ((ctx->d & ctx->b) | (~(ctx->d) & ctx->c));
}

uint32_t	md5_h(t_ctx *ctx)
{
	return (ctx->b ^ ctx->c ^ ctx->d);
}

uint32_t	md5_i(t_ctx *ctx)
{
	return (ctx->c ^ (ctx->b | ~(ctx->d)));
}
