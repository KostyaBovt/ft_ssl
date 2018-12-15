#include "../includes/ft_ssl.h"

t_ctx *init_ctx()
{
	t_ctx *new;

	new = (t_ctx*)malloc(sizeof(t_ctx));
	new->a = 0x67452301;
	new->b = 0xefcdab89;
	new->c = 0x98badcfe;
	new->d = 0x10325476;
	return new;
}

t_ctx *copy_ctx(t_ctx *ctx)
{
	t_ctx *new;

	new = (t_ctx*)malloc(sizeof(t_ctx));
	new->a = ctx->a;
	new->b = ctx->b;
	new->c = ctx->c;
	new->d = ctx->d;
	return new;
}

void print_ctx(t_ctx *ctx)
{
	write(1, "A: ", 3);
	ft_print_memory(&(ctx->a), sizeof(uint32_t), 0);
	write(1, "\n", 1);
	write(1, "B: ", 3);
	ft_print_memory(&(ctx->b), sizeof(uint32_t), 0);
	write(1, "\n", 1);
	write(1, "C: ", 3);
	ft_print_memory(&(ctx->c), sizeof(uint32_t), 0);
	write(1, "\n", 1);
	write(1, "D: ", 3);
	ft_print_memory(&(ctx->d), sizeof(uint32_t), 0);
	write(1, "\n", 1);
}