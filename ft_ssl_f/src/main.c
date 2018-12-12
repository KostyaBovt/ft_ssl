#include "../includes/ft_ssl.h"

int main(int argc, char **argv)
{
	t_global *global;

	global = init_global(argc, argv);
	make_hash(global);
	return(0);
}