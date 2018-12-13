#include "../includes/ft_ssl.h"

void	process_stdin(t_global *g)
{
	g->input_was = 1;
	ft_printf("we in process_stdin %s\n", g->mock);
}
