#include "../includes/ft_ssl.h"

void	process_stdin(t_global *g)
{
	t_fd_iterator *fd_iterator;
	void	*block;
	t_ctx	*ctx;
	t_hash *hash;

	g->input_was = 1;
	// ft_printf("we in process_stdin %s\n", g->mock);

	g->input_msg = "stdin";
	g->input_type = 'i';

	//create context
	ctx = init_ctx();
	
	//read file by blocks of 512 bits (64 bytes)
	if (!(fd_iterator = init_fd_iterator(g, 0)))
		return;
	while ((block = fd_iterator->next((void*)fd_iterator)))
		//pass block and context in loop to hashing function
		calculate_block_hash(g, ctx, block);

	hash = compile_hash(g, ctx);
	output_hash(g, hash);
}
