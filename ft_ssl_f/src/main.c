#include "../includes/ft_ssl.h"

void print_leaks()
{
	ft_printf("%.20s : %zu\n", "t_hash", sizeof(t_hash));
	ft_printf("%.20s : %zu\n", "t_global", sizeof(t_global));
	ft_printf("%.20s : %zu\n", "t_str_iterator", sizeof(t_str_iterator));
	ft_printf("%.20s : %zu\n", "t_fd_iterator", sizeof(t_fd_iterator));
	ft_printf("%.20s : %zu\n", "t_ctx", sizeof(t_ctx));
}

int main(int ac, char **av)
{
	t_global *g;

	// print_leaks();
	// return(0);
	g = init_global(ac, av);
	call_main_controller(g);
	// while(1);
	return(0);
}
