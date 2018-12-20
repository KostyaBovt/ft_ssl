#include "../includes/ft_ssl.h"

void	process_file(t_global *g, char *file)
{
	t_ctx	*ctx;
	void	*block;
	t_fd_iterator *fd_iterator;
	int fd;
	char *hash;
	int i;

	g->reach_files = 1;
	g->input_was = 1;
	ft_printf("we in process_file %s %s\n", file, g->mock);

	if ((fd = open(file, O_RDONLY)) < 0)
	{
		print_erorr_file(file);
		return;
	}

	//create context
	ctx = init_ctx();
	
	//read file by blocks of 512 bits (64 bytes)
	if (!(fd_iterator = init_fd_iterator(g, fd)))
		return;
	while ((block = fd_iterator->next((void*)fd_iterator)))
		//pass block and context in loop to hashing function
		calculate_block_hash(g, ctx, block);


	hash = compile_hash(g, ctx);
	i = -1;
	while (++i < 8)
		ft_printf("%X ", ((uint32_t*)hash)[i]);
	ft_printf("\n");

	// return result hash
	// ft_printf("\nFINAL HASH: %16m STOP\n", (void*)compile_hash(g, ctx));
	// return compile_hash(ctx);
}

t_fd_iterator	*init_fd_iterator(t_global *g, int fd)
{
	t_fd_iterator	*new;

	new = (t_fd_iterator*)malloc(sizeof(t_fd_iterator));
	new->fd = fd;
	new->total_len = 0;
	new->full_blocks_n = 0;
	new->full_blocks_returned = 0;
	new->last_block_len = 0;
	new->last_blocks_n = 0;
	new->last_blocks_returned = 0;
	new->next = &next_block_fd;
	new->g = g;
	return new;
}


void			*next_block_fd(void *self_void)
{
	t_fd_iterator *self;
	char	*buf;
	int rd;

	buf = (char*)malloc(64);
	self = (t_fd_iterator*)self_void;
	if (self->last_blocks_n == self->last_blocks_returned && self->last_blocks_n)
		return NULL;
	if (self->last_blocks_returned == 1) {
		self->last_blocks_returned = 2;
		return make_last_padded_block(self->g, self->total_len);
	}
	rd = read(self->fd, buf, 64);
	if (rd == 64)
	{
		self->total_len += 64;
		return buf;
	}
	if (rd != 64)
	{
		self->last_block_len = rd;
		self->total_len += rd;
		self->last_blocks_n = self->last_block_len < 56 ? 1 : 2;
		self->last_blocks_returned = 1;
		return make_padded_block(self->g, (void*)(buf), self->last_block_len, self->total_len);
	}
	return NULL;
}

