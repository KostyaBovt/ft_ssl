#include "../includes/ft_ssl.h"

void	*make_last_padded_block(int msg_len)
{
	void *new_block;
	uint64_t n;

	n = msg_len;
	new_block = (void*)malloc(64);
	ft_bzero(new_block, 64);
	ft_memcpy(&new_block[56], &n, 8);
	return new_block;
}

void	*make_padded_block(void *block_start, int last_block_len, int msg_len)
{
	unsigned char determinator;
	void *new_block;
	uint64_t n;

	new_block = (void*)malloc(64);
	ft_bzero(new_block, 64);
	ft_memcpy(new_block, block_start, last_block_len);
	determinator = 128;
	ft_memcpy(&new_block[last_block_len], &determinator, 1);

	if (last_block_len < 56) {
		n = msg_len;
		ft_memcpy(&new_block[56], &n, 8);
	}
	return new_block;
}