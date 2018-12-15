#include "../includes/ft_ssl.h"

uint32_t md5_F(t_ctx *ctx)
{
	return ((ctx->b & ctx->c) | (~(ctx->b) & ctx->d));
}

uint32_t md5_G(t_ctx *ctx)
{
	return ((ctx->d & ctx->b) | (~(ctx->d) & ctx->c));
}

uint32_t md5_H(t_ctx *ctx)
{
	return (ctx->b ^ ctx->c ^ ctx->d);
}

uint32_t md5_I(t_ctx *ctx)
{
	return (ctx->c ^ (ctx->b | ~(ctx->d)));
}
