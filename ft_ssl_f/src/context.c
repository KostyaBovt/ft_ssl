#include "../includes/ft_ssl.h"

t_ctx *init_ctx()
{
	t_ctx *new;

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
	new->h0 = ctx->h0;
	new->h1 = ctx->h1;
	new->h2 = ctx->h2;
	new->h3 = ctx->h3;
	new->h4 = ctx->h4;
	new->h5 = ctx->h5;
	new->h6 = ctx->h6;
	new->h7 = ctx->h7;
	return new;
}

void print_ctx(t_ctx *ctx)
{
	write(1, "A: ", 3);
	// ft_print_memory(&(ctx->a), sizeof(uint32_t), 0);
	ft_printf("%zu", ctx->a);
	write(1, "\n", 1);
	write(1, "B: ", 3);
	ft_printf("%zu", ctx->b);
	// ft_print_memory(&(ctx->b), sizeof(uint32_t), 0);
	write(1, "\n", 1);
	write(1, "C: ", 3);
	// ft_putnbr(ctx->c);
	ft_printf("%zu", ctx->c);
	// ft_print_memory(&(ctx->c), sizeof(uint32_t), 0);
	write(1, "\n", 1);
	write(1, "D: ", 3);
	ft_printf("%zu", ctx->d);
	// ft_print_memory(&(ctx->d), sizeof(uint32_t), 0);
	write(1, "\n", 1);
}

void merge_ctx(t_ctx *ctx, t_ctx *temp_ctx)
{
	ctx->a += temp_ctx->a;
	ctx->b += temp_ctx->b;
	ctx->c += temp_ctx->c;
	ctx->d += temp_ctx->d;
}