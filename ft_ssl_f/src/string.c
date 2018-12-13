#include "../includes/ft_ssl.h"

void	process_string(t_global *g)
{
	g->input_was = 1;
	if (g->ac - 1 == g->av_i) // if this is last av
	{
		print_erorr_s();
		print_usage_md5();
		exit(EXIT_SUCCESS);
	}
	else
		(g->av_i)++;
		ft_printf("we in process_string %s %s\n", g->av[g->av_i], g->mock);
		make_hash_string(g->av[g->av_i]);
}

void	make_hash_string(char *str)
{
	t_ctx	*ctx;

	ctx = init_ctx();
	//create context
	//iterate string over blocks of 512 bits (64 bytes)
	//pass block and context in loop to hashing function
	// print context as result hash

}