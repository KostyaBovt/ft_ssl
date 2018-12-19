#include "../includes/ft_ssl.h"

const uint32_t K2[] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

void			calc_block_hash_sha256(t_ctx *ctx, void *block)
{
	uint32_t *M;
	uint32_t s0;
	uint32_t s1;
	uint32_t E0;
	uint32_t E1;
	uint32_t Ma;
	uint32_t t1;
	uint32_t t2;
	uint32_t Ch;
	int i;
	t_ctx *t_ctx;

	M = devide_block_sha256(block);
	i = 15;
	while (++i < 64)
	{

	    s0 = (ft_rotr(M[i - 15], 7)) ^ (ft_rotr(M[i - 15], 18)) ^ (M[i - 15] >> 3);
	    s1 = (ft_rotr(M[i - 2], 17)) ^ (ft_rotr(M[i - 2], 19)) ^ (M[i - 2] >> 10);
	    M[i] = M[i - 16] + s0 + M[i - 7] + s1;
	}

	ft_printf("calc_block_hash_md5\n");
	ft_printf("\n=================\n");
	ft_printf("CALULATING BLOCK 512\n");
	ft_printf("CTX BEFORE:\n");
	print_ctx(ctx);
	ft_printf("\nBLOCK 512\n");
	ft_print_memory((void*)M, 256, "dc");
	print_block_sha256(M);
	ft_printf("\n");

	t_ctx = copy_ctx(ctx);

    i = -1;
    while (++i < 64) 
    {
        E0 = (ft_rotr(t_ctx->h0, 2)) ^ (ft_rotr(t_ctx->h0, 13)) ^ (ft_rotr(t_ctx->h0, 22));
        Ma = (t_ctx->h0 & t_ctx->h1) ^ (t_ctx->h0 & t_ctx->h2) ^ (t_ctx->h1 & t_ctx->h2);
        t2 = E0 + Ma;
        E1 = (ft_rotr(t_ctx->h4, 6)) ^ (ft_rotr(t_ctx->h4, 11)) ^ (ft_rotr(t_ctx->h4, 25));
        Ch = (t_ctx->h4 & t_ctx->h5) ^ ((~(t_ctx->h4)) & t_ctx->h6);
        t1 = t_ctx->h7 + E1 + Ch + K2[i] + M[i];

       	t_ctx->h7 = t_ctx->h6;
       	t_ctx->h6 = t_ctx->h5;
       	t_ctx->h5 = t_ctx->h4;
       	t_ctx->h4 = t_ctx->h3 + t1;
       	t_ctx->h3 = t_ctx->h2;
       	t_ctx->h2 = t_ctx->h1;
       	t_ctx->h1 = t_ctx->h0;
       	t_ctx->h0 = t1 + t2;
   	    ft_printf("TEMP CTX after iteration [%d]:\n", i);
	    print_ctx_hex(t_ctx);
    }
    merge_ctx(ctx, t_ctx);
    ft_printf("CTX after BLOCK 512:\n");
    print_ctx_hex(ctx);
}


uint32_t *devide_block_sha256(void *block)
{
	int i;
	uint32_t *new;
	uint32_t *old;

	old = (uint32_t*)block;
	new = (uint32_t*)malloc(256);
	ft_bzero(new, 256);
	i = -1;
	while (++i < 16)
	{
		ft_memcpy_rot(&(new[i]), &(old[i]), 4);
	}
	return new;
}

char *compile_hash_sha256(t_ctx *ctx)
{
	void *temp;

	temp = (void*)malloc(32);
	ft_memcpy(temp, &(ctx->h0), 4);
	ft_memcpy(&temp[4], &(ctx->h1), 4);
	ft_memcpy(&temp[8], &(ctx->h2), 4);
	ft_memcpy(&temp[12], &(ctx->h3), 4);
	ft_memcpy(&temp[16], &(ctx->h4), 4);
	ft_memcpy(&temp[20], &(ctx->h5), 4);
	ft_memcpy(&temp[24], &(ctx->h6), 4);
	ft_memcpy(&temp[28], &(ctx->h7), 4);
	return (char*)temp;
}

void print_block_sha256(uint32_t *block)
{
	int i;

	i = 0;
	while (i < 64)
	{
		ft_printf("word [%d]: %X\n", i, block[i]);
		i++;
	}
}