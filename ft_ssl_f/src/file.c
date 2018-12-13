#include "../includes/ft_ssl.h"

void	process_file(t_global *g, char *file)
{
	g->reach_files = 1;
	g->input_was = 1;
	ft_printf("we in process_file %s %s\n", file, g->mock);
}
