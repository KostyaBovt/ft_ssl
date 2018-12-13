#include "../includes/ft_ssl.h"

t_global *init_global(int ac, char **av)
{
	t_global	*new_global;

	new_global = (t_global*)malloc(sizeof(t_global));
	new_global->ac = ac;
	new_global->av = av;
	new_global->r = 0;
	new_global->q = 0;
	new_global->av_i = 1;
	new_global->reach_files = 0;
	new_global->input_was = 0;
	new_global->mock = "mock";
	return(new_global);
}