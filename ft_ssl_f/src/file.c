/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbovt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 18:18:44 by kbovt             #+#    #+#             */
/*   Updated: 2018/12/24 18:18:46 by kbovt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void			process_file(t_global *g, char *file)
{
	t_ctx			*ctx;
	void			*block;
	t_fd_iterator	*fd_iterator;
	int				fd;
	t_hash			*hash;

	g->reach_files = 1;
	g->input_was = 1;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (print_erorr_file(file));
	g->input_msg = file;
	g->input_type = 'f';
	ctx = init_ctx();
	if (!(fd_iterator = init_fd_iterator(g, fd)))
		return ;
	while ((block = fd_iterator->next((void*)fd_iterator)))
	{
		calculate_block_hash(g, ctx, block);
		free(block);
	}
	free(fd_iterator);
	hash = compile_hash(g, ctx);
	free(ctx);
	output_hash(g, hash);
	free_t_hash(&hash);
}

t_fd_iterator	*init_fd_iterator(t_global *g, int fd)
{
	t_fd_iterator	*new;

	new = (t_fd_iterator*)malloc(sizeof(t_fd_iterator));
	new->fd = fd;
	new->total_len = 0;
	new->full_blocks_n = 0;
	new->full_blocks_returned = 0;
	new->last_block_len = 0;
	new->last_blocks_n = 0;
	new->last_blocks_returned = 0;
	new->next = &next_block_fd;
	new->g = g;
	return (new);
}

void			*next_block_fd(void *self_void)
{
	t_fd_iterator	*self;
	char			*buf;
	int				rd;

	self = (t_fd_iterator*)self_void;
	if (self->last_blocks_n == self->last_blocks_returned \
		&& self->last_blocks_n)
		return (NULL);
	if (self->last_blocks_returned == 1)
	{
		self->last_blocks_returned = 2;
		return (make_last_padded_block(self->g, self->total_len));
	}
	buf = (char*)malloc(64);
	rd = read(self->fd, buf, 64);
	if (rd == 64)
	{
		self->last_block_len = 64;
		self->total_len += 64;
		return (buf);
	}
	if (rd != 64)
		return (pr_pad(self, rd, buf));
	return (NULL);
}

void			*pr_pad(t_fd_iterator *self, int rd, char *buf)
{
	void	*block;

	self->last_block_len = rd;
	self->total_len += rd;
	self->last_blocks_n = self->last_block_len < 56 ? 1 : 2;
	self->last_blocks_returned = 1;
	block = make_padded_block(self->g, \
		(void*)(buf), self->last_block_len, self->total_len);
	free(buf);
	return (block);
}
