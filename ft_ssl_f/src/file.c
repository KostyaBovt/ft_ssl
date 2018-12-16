#include "../includes/ft_ssl.h"

void	process_file(t_global *g, char *file)
{
	t_ctx	*ctx;
	void	*block;
	t_file_iterator *file_iterator;

	g->reach_files = 1;
	g->input_was = 1;
	ft_printf("we in process_file %s %s\n", file, g->mock);

	//create context
	ctx = init_ctx();
	
	//read file by blocks of 512 bits (64 bytes)
	if (!(file_iterator = init_file_iterator(file)))
		return;
	while ((block = file_iterator->next((void*)file_iterator)))
		//pass block and context in loop to hashing function
		calculate_block_hash(ctx, block);

	// return result hash
	return compile_hash(ctx);
}

t_file_iterator	*init_file_iterator(char *file)
{
	t_file_iterator	*new;
	int fd;

	if  ((fd = open(av[i], O_RDONLY)) < 0)
	{
		print_erorr_file(file);
		return NULL;
	}

	new = (t_file_iterator*)malloc(sizeof(t_file_iterator));
	new->file = file;
	new->full_blocks_n = 0;
	new->fd = fd;
	new->full_blocks_returned = 0;
	new->last_block_len = 0;
	new->last_blocks_n = 0;
	new->last_blocks_returned = 0;
	new->next = &next_block_file;
	return new;
}


void			*next_block_str(void *self_void)
{
	void *final_block;
	t_file_iterator *self;
	char	buf[65];
	int rd;

	self = (t_file_iterator*)self_void;

	while ((rd = read(self->fd, buf, 64)) > 0)
	{
		
	}

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

