#include "../includes/ft_ssl.h"

void	*make_last_padded_block(int msg_len);
{
	void *block;

	block = (void*)malloc(64);
	
}

void	*make_padded_block(void *block_start, int *last_block_len, int msg_len)
{

}