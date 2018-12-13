#include "../includes/ft_ssl.h"

int main(int ac, char **av)
{
	t_global *g;

	g = init_global(ac, av);
	call_main_controller(g);
	return(0);
}