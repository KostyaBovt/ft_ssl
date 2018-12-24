/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbovt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 18:22:38 by kbovt             #+#    #+#             */
/*   Updated: 2018/12/24 18:22:40 by kbovt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void	call_main_controller(t_global *g)
{
	check_command(g);
	while (++(g->av_i) < g->ac)
		process_av(g, g->av[g->av_i]);
	if (!g->input_was)
		process_stdin(g, 0);
}

void	process_av(t_global *g, char *av)
{
	if (!ft_strcmp(av, "-p") && !g->reach_files)
		process_stdin(g, 1);
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
