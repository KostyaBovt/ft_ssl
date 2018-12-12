/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 04:07:55 by kchernia          #+#    #+#             */
/*   Updated: 2018/10/19 08:24:43 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <libft.h>

int	ssl_live_mode(t_ssl_cmd *cmd)
{
	char	*line;
	int		rd;

	cmd->flags.p = 0;
	while (ft_printf("ft_ssl> ") &&
		(rd = get_next_line(STDIN_FILENO, &line)) > 0)
	{
		if (check_cmd(line, cmd))
			process_stdin(cmd);
		else if (*line != 0)
			print_cmd_list(line);
		free(line);
	}
	return (rd);
}

int	main(int ac, char **av)
{
	t_ssl_cmd	cmd;

	if (ac == 1)
		return (ssl_live_mode(&cmd));
	if (!parse_flags(av, &cmd))
		return (print_cmd_list(av[1]));
	if (ac == (2 + cmd.flags.p + cmd.flags.q + cmd.flags.r) || cmd.flags.p)
		process_stdin(&cmd);
	process_strings(av, &cmd);
	process_files(av, &cmd);
	return (0);
}
