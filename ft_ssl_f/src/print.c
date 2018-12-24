/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbovt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 18:23:05 by kbovt             #+#    #+#             */
/*   Updated: 2018/12/24 18:23:07 by kbovt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void	print_erorr_s(void)
{
	ft_printf("md5: option requires an argument -- s\n");
}

void	print_erorr_file(char *file)
{
	ft_printf("md5: %s: No such file or directory\n", file);
}

void	print_erorr_command(char *command)
{
	ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n", command);
	ft_printf("Standard commands:\n\nMessage Digest commands:\n");
	ft_printf("md5\nsha256\n\nCipher commands:\n");
}

void	print_usage_command(char *command)
{
	ft_printf("usage: %s [-pqrtx] [-s string] [files ...]\n", command);
}

void	print_usage_ssl(void)
{
	ft_printf("usage: ft_ssl command [command opts] [command args]\n");
}
