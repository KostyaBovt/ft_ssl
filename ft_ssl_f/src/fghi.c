#include "../includes/ft_ssl.h"

uint32_t md5_F(t_ctx *ctx)
{
	uint32_t ret;
	ret = ((ctx->b & ctx->c) | (~(ctx->b) & ctx->d));

	// ft_printf("md5_F(B,C,D) = B and C or not(B) and D = %zu and %zu or not(%zu) and %zu = %zu\n", ctx->b, ctx->c, ctx->b, ctx->d, ret);
	return ret;
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
