#include "../includes/ft_ssl.h"

t_global *init_global(int argc, char **argv)
{
	t_global	*new_global;

	new_global = (t_global*)malloc(sizeof(t_global));
	new_global->argc = argc;
	new_global->argv = argv;
	return(new_global);
}