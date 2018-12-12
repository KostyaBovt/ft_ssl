/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 18:16:04 by kchernia          #+#    #+#             */
/*   Updated: 2018/10/19 04:26:08 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <sys/types.h>
# include <stdint.h>
# include <fcntl.h>

# include <libft.h>
# include <ft_md5.h>
# include <ft_sha256.h>

typedef char*(*t_func_ptr)(t_string msg);

typedef struct		s_func_pair
{
	char			*func_name;
	char			*u_func_name;
	t_func_ptr		func;
}					t_func_pair;

extern t_func_pair	g_func_arr[];

typedef struct		s_ssl_flags
{
	int				p;
	int				q;
	int				r;
	int				s_i;
}					t_ssl_flags;

typedef struct		s_ssl_cmd
{
	t_func_pair		func_pair;
	t_ssl_flags		flags;
}					t_ssl_cmd;

void				process_stdin(t_ssl_cmd *cmd);
void				process_strings(char **av, t_ssl_cmd *cmd);
void				process_files(char **av, t_ssl_cmd *cmd);

int					check_cmd(const char *cmd, t_ssl_cmd *ssl_cmd);
int					parse_flags(char **av, t_ssl_cmd *cmd);

int					print_cmd_list(char *cmd);
void				print_str_error(t_ssl_cmd *cmd);
void				print_file_error(t_ssl_cmd *cmd, char *file);
void				print_dgst_stdin(char *dgst, char *msg, t_ssl_cmd *cmd);
void				print_dgst_str(char *dgst, char *msg,
									t_ssl_cmd *cmd, char *c);

#endif
