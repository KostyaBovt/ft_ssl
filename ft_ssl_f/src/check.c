#include "../includes/ft_ssl.h"


void	check_command(t_global *g)
{
	char	*commands[3];
	int		i;

	if (g->ac < 2)
	{
		print_usage_ssl();
		exit(EXIT_FAILURE);
	}

	commands[0] = "md5";
	commands[1] = "sha256";
	commands[2] = NULL;
	i = -1;
	while (commands[++i])
		if (!ft_strcmp(commands[i], g->av[1]))
				return;
	
	print_erorr_command(g->av[1]);
	exit(EXIT_FAILURE);
}