#include "../includes/ft_ssl.h"

void	process_stdin(t_global *g)
{
	t_fd_iterator *fd_iterator;
	void	*block;
	t_ctx	*ctx;

	g->input_was = 1;
	ft_printf("we in process_stdin %s\n", g->mock);

	//create context
	ctx = init_ctx();
	
	//read file by blocks of 512 bits (64 bytes)
	if (!(fd_iterator = init_fd_iterator(0)))
		return;
	while ((block = fd_iterator->next((void*)fd_iterator)))
		//pass block and context in loop to hashing function
		calculate_block_hash(ctx, block);

	// return result hash
	ft_printf("\nFINAL HASH: %16m STOP\n", (void*)compile_hash(ctx));
	// return compile_hash(ctx);

}
