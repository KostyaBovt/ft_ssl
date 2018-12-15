#include "../includes/ft_ssl.h"

void			process_string(t_global *g)
{
	char *hash;

	g->input_was = 1;
	if (g->ac - 1 == g->av_i) // if this is last av
	{
		print_erorr_s();
		print_usage_md5();
		exit(EXIT_SUCCESS);
	}
	else
	{
		(g->av_i)++;
		ft_printf("we in process_string %s %s\n", g->av[g->av_i], g->mock);
		hash = make_hash_string(g->av[g->av_i]);
		ft_printf("\nFINAL HASH: %s\n", hash);
		// print_hash(hash, g);
	}
}

char			*make_hash_string(char *str)
{
	t_ctx	*ctx;
	void	*block;
	t_str_iterator *str_iterator;

	//create context
	ctx = init_ctx();
	
	//iterate string over blocks of 512 bits (64 bytes)
	str_iterator = init_str_iterator(str);
	while ((block = str_iterator->next((void*)str_iterator)))
		//pass block and context in loop to hashing function
		calculate_block_hash(ctx, block);

	// return result hash
	return compile_hash(ctx);
}

t_str_iterator	*init_str_iterator(char *str)
{
	t_str_iterator	*new;

	new = (t_str_iterator*)malloc(sizeof(t_str_iterator));
	new->str = str;
	new->str_len = ft_strlen(str);
	new->str_i = 0;
	new->full_blocks_n = new->str_len / 64;
	new->full_blocks_returned = 0;
	new->last_block_len = new->str_len % 64;
	new->last_blocks_n = new->last_block_len < 56 ? 1 : 2;
	new->last_blocks_returned = 0;
	new->next = &next_block_str;

	return new;
}

void			*next_block_str(void *self_void)
{
	void *final_block;
	t_str_iterator *self;

	self = (t_str_iterator*)self_void;

	if (self->full_blocks_returned < self->full_blocks_n)
	{
		final_block = (void*)(&(self->str[self->str_i]));
		(self->full_blocks_returned)++;
		self->str_i += 64;
		return final_block;
	}
	else if (self->last_blocks_returned < self->last_blocks_n)
	{
		if (self->last_blocks_returned == 1)
			final_block = make_last_padded_block(self->str_len);
		else
			final_block = make_padded_block((void*)(&(self->str[self->str_i])), self->last_block_len, self->str_len);
		
		(self->last_blocks_returned)++;
		return final_block;
	}
	else
		return NULL;
}