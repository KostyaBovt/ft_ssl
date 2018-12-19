#include "../includes/ft_ssl.h"


void			calculate_block_hash(t_global *g, t_ctx *ctx, void *block)
{
	ft_printf("calculate_block_hash\n");
	if (!ft_strcmp(g->alg, "md5"))
		calc_block_hash_md5(ctx, block);
	if (!ft_strcmp(g->alg, "sha256"))
		calc_block_hash_sha256(ctx, block);
}

char *compile_hash(t_global *g, t_ctx *ctx)
{
	if (!ft_strcmp(g->alg, "md5"))
		return compile_hash_md5(ctx);
	if (!ft_strcmp(g->alg, "sha256"))
		return compile_hash_sha256(ctx);
	return NULL;
}