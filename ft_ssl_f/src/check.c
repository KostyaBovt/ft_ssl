/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbovt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 18:18:11 by kbovt             #+#    #+#             */
/*   Updated: 2018/12/24 18:18:15 by kbovt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void	check_command(t_global *g)
{
	char	*commands[3];
	char	*print_commands[3];
	int		i;

	if (g->ac < 2)
	{
		print_usage_ssl();
		exit(EXIT_FAILURE);
	}
	commands[0] = "md5";
	commands[1] = "sha256";
	commands[2] = NULL;
	print_commands[0] = "MD5";
	print_commands[1] = "SHA256";
	i = -1;
	while (commands[++i])
		if (!ft_strcmp(commands[i], g->av[1]))
		{
			g->alg = commands[i];
			g->alg_print = print_commands[i];
			return ;
		}
	print_erorr_command(g->av[1]);
	exit(EXIT_FAILURE);
}
