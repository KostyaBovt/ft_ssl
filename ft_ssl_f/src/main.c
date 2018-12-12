#include "../includes/ft_ssl.h"

int main(int argc, char **argv)
{
	t_global *global;

	global = init_global(argc, argv);
	call_main_controller(global);
	return(0);
}