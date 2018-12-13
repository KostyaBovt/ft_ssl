#include "../includes/ft_ssl.h"

void	call_main_controller(t_global *g)
{
	check_command(g);
	while (++(g->av_i) < g->ac)
		process_av(g, g->av[g->av_i]);
	if (!g->input_was)
		process_stdin(g);
}

void	process_av(t_global *g, char *av)
{
	if (!ft_strcmp(av, "-p") && !g->reach_files)
		process_stdin(g);
	else if (!ft_strcmp(av, "-s") && !g->reach_files)
		process_string(g);
	else if ((!ft_strcmp(av, "-q") || !ft_strcmp(av, "-r")) && !g->reach_files)
		add_flag(g, av);
	else
		process_file(g, av);
}

void	add_flag(t_global *g, char *flag)
{
	if (!ft_strcmp(flag, "-q"))
		g->q = 1;
	if (!ft_strcmp(flag, "-r"))
		g->r = 1;
}
