/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 07:03:35 by kchernia          #+#    #+#             */
/*   Updated: 2018/10/19 08:09:21 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <libft.h>

int		print_cmd_list(char *cmd)
{
	ft_printf("ft_ssl: Error '%s' is an invalid command.\n", cmd);
	ft_printf("\nStandard commands:\n");
	ft_printf("\nMessage Digest commands:\nmd5\nsha256\n");
	ft_printf("\nCipher commands:\n");
	return (1);
}

void	print_str_error(t_ssl_cmd *cmd)
{
	ft_printf("%s: option requires an argument -- s\n",
				cmd->func_pair.func_name);
	ft_printf("usage: %s [-pqr] [-s string] [files ...]\n",
				cmd->func_pair.func_name);
}

void	print_file_error(t_ssl_cmd *cmd, char *file)
{
	ft_printf("ft_ssl: %s: %s: No such file or directory\n",
				cmd->func_pair.func_name, file);
}

void	print_dgst_stdin(char *dgst, char *msg, t_ssl_cmd *cmd)
{
	if (cmd->flags.p)
		ft_printf("%s", msg);
	ft_printf("%s\n", dgst);
}

void	print_dgst_str(char *dgst, char *msg, t_ssl_cmd *cmd, char *c)
{
	if (cmd->flags.q)
		ft_printf("%s\n", dgst);
	else if (cmd->flags.r)
		ft_printf("%s %s%s%s\n", dgst, c, msg, c);
	else
		ft_printf("%s (%s%s%s) = %s\n",
				cmd->func_pair.u_func_name, c, msg, c, dgst);
}
