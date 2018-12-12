/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 07:20:12 by kchernia          #+#    #+#             */
/*   Updated: 2018/10/19 08:25:29 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ssl.h>
#include <libft.h>

static char		*resize_msg(char *msg, size_t size, size_t new_size)
{
	char		*tmp;
	size_t		i;

	tmp = (char*)malloc(sizeof(char) * (new_size + 1));
	tmp[new_size] = 0;
	i = 0;
	while (i < size)
	{
		tmp[i] = msg[i];
		i++;
	}
	while (i < new_size)
	{
		tmp[i] = 0;
		i++;
	}
	free(msg);
	return (tmp);
}

static t_string	read_file_content(int fd)
{
	t_string	msg;
	size_t		total_len;
	ssize_t		rd;
	char		buf[BUFF_SIZE + 1];

	msg.data = 0;
	total_len = 0;
	msg.len = 0;
	while ((rd = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[rd] = 0;
		if (msg.len + rd > total_len)
		{
			msg.data = resize_msg(msg.data, total_len,
							(total_len * 2 + rd));
			total_len = total_len * 2 + rd;
		}
		ft_memcpy(msg.data + msg.len, buf, (size_t)rd);
		msg.len += rd;
	}
	if (msg.data == 0 && rd == 0)
		msg.data = ft_strnew(0);
	return (msg);
}

void			process_stdin(t_ssl_cmd *cmd)
{
	char		*dgst;
	t_string	msg;

	msg = read_file_content(STDIN_FILENO);
	dgst = cmd->func_pair.func(msg);
	print_dgst_stdin(dgst, msg.data, cmd);
	free(msg.data);
	free(dgst);
}

void			process_strings(char **av, t_ssl_cmd *cmd)
{
	int		i;
	char	*dgst;

	i = cmd->flags.s_i;
	while (av[i] && !ft_strcmp(av[i], "-s"))
	{
		if (!av[i + 1])
		{
			print_str_error(cmd);
			break ;
		}
		else
		{
			dgst = cmd->func_pair.func((t_string){av[i + 1],
										ft_strlen(av[i + 1])});
			print_dgst_str(dgst, av[i + 1], cmd, "\"");
			free(dgst);
		}
		i += 2;
		cmd->flags.s_i = i;
	}
}

void			process_files(char **av, t_ssl_cmd *cmd)
{
	t_string	msg;
	char		*dgst;
	int			fd;
	int			i;

	i = cmd->flags.s_i;
	while (av[i])
	{
		if ((fd = open(av[i], O_RDONLY)) > 0)
		{
			msg = read_file_content(fd);
			dgst = cmd->func_pair.func(msg);
			print_dgst_str(dgst, av[i], cmd, "");
			free(msg.data);
			free(dgst);
		}
		else
			print_file_error(cmd, av[i]);
		i++;
	}
}
