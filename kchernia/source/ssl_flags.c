/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 07:15:50 by kchernia          #+#    #+#             */
/*   Updated: 2018/10/19 08:06:12 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <libft.h>

static void	init_flags(t_ssl_flags *flags)
{
	flags->p = 0;
	flags->q = 0;
	flags->r = 0;
	flags->s_i = 0;
}

int			check_cmd(const char *cmd, t_ssl_cmd *ssl_cmd)
{
	int	i;

	i = 0;
	while (g_func_arr[i].func_name != 0)
	{
		if (!ft_strcmp(cmd, g_func_arr[i].func_name))
		{
			ssl_cmd->func_pair = g_func_arr[i];
			return (1);
		}
		i++;
	}
	return (0);
}

int			parse_flags(char **av, t_ssl_cmd *cmd)
{
	int	i;

	init_flags(&cmd->flags);
	if (!check_cmd(av[1], cmd))
		return (0);
	i = 2;
	while (av[i])
	{
		if (!ft_strcmp(av[i], "-p"))
			cmd->flags.p += 1;
		else if (!ft_strcmp(av[i], "-q"))
			cmd->flags.q += 1;
		else if (!ft_strcmp(av[i], "-r"))
			cmd->flags.r += 1;
		else
			break ;
		i++;
	}
	cmd->flags.s_i = i;
	return (1);
}
