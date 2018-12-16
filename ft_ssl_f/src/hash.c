#include "../includes/ft_ssl.h"
#include <inttypes.h>

const uint32_t	S[] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

const uint32_t	K[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

void			calculate_block_hash(t_ctx *ctx, void *block)
{

	ft_printf("\n=================\n");
	ft_printf("CALULATING BLOCK 512\n");
	ft_printf("CTX BEFORE:\n");
	print_ctx(ctx);
	ft_printf("\nBLOCK 512\n");
	ft_print_memory(block, 64, "dc");
	print_block((uint32_t*)block);
	ft_printf("\n");

	uint32_t *M;
	t_ctx *temp_ctx;
	int i;
	int g;
	uint32_t F;
	// uint64_t F_temp;

	M = devide_block(block);
	temp_ctx = copy_ctx(ctx);

	i = -1;
	while (++i < 64)
	{
		if (i < 16)
			F = md5_F(temp_ctx);
		else if (i < 32)
			F = md5_G(temp_ctx);
		else if (i < 48)
			F = md5_H(temp_ctx);
		else
			F = md5_I(temp_ctx);
		g = get_word_i(i);
		ft_printf("F = a + F(b,c,d) + X[k] + T[i] = %zu + %zu + %zu + %zu = %" PRId64 "\n", temp_ctx->a, F, K[i], M[g], temp_ctx->a + F + K[i] + M[g]);
		F = temp_ctx->a + F + K[i] + M[g];
		temp_ctx->a = temp_ctx->d;
		temp_ctx->d = temp_ctx->c;
		temp_ctx->c = temp_ctx->b;
		ft_printf("b + (F << S[i]) = b + (%zu << %zu)= %zu + %zu = %zu\n", F, S[i], temp_ctx->b, (F << S[i]), temp_ctx->b + (F << S[i]));
		temp_ctx->b = temp_ctx->b + ((F << S[i]) | (F >> (32 - S[i])));
		ft_printf("TEMP_CTX AFTER [%d]/[63] cycle:\n", i);
		print_ctx(temp_ctx);
	}
	merge_ctx(ctx, temp_ctx);
	ft_printf("CTX AFTER:\n");
	print_ctx(ctx);
}

char *compile_hash(t_ctx *ctx)
{
	void *temp;

	temp = (void*)malloc(16);
	ft_memcpy(temp, &(ctx->a), 4);
	ft_memcpy(&temp[4], &(ctx->b), 4);
	ft_memcpy(&temp[8], &(ctx->c), 4);
	ft_memcpy(&temp[12], &(ctx->d), 4);
	return (char*)temp;
}

uint32_t *devide_block(void *block)
{
	return (uint32_t*)block;
}

int get_word_i(int i)
{
	if (i < 16)
		return i;
	else if (i < 32)
		return (5 * i + 1) % 16;
	else if (i < 48)
		return (3 * i + 5) % 16;
	else
		return (7 * i) % 16;
}

void print_block(uint32_t *block)
{
	int i;

	i = 0;
	while (i < 16)
	{
		ft_printf("word [%d]: %zu\n", i, block[i]);
		i++;
	}
}