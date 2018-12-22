#include "../includes/ft_ssl.h"

void free_t_global(t_global **g_p)
{	
	t_global *g;

	g = *g_p;

	// free(g->alg);
	// free(g->alg_print);
	// free(g->input_msg);
	// free(g->mock);
	free(*g_p);
}

void free_t_hash(t_hash **hash)
{
	free((*hash)->hash);
	free(*hash);
}