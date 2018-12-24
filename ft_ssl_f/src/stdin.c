/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbovt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 18:23:15 by kbovt             #+#    #+#             */
/*   Updated: 2018/12/24 18:23:22 by kbovt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void	process_stdin(t_global *g, char verbose)
{
	t_fd_iterator	*fd_iterator;
	void			*block;
	t_ctx			*ctx;
	t_hash			*hash;

	if (verbose)
		g->input_was = 1;
	g->input_type = 'i';
	ctx = init_ctx();
	if (!(fd_iterator = init_fd_iterator(g, 0)))
		return ;
	while ((block = fd_iterator->next((void*)fd_iterator)))
	{
		append_to_msg(g, block, fd_iterator);
		calculate_block_hash(g, ctx, block);
		free(block);
	}
	free(fd_iterator);
	hash = compile_hash(g, ctx);
	free(ctx);
	output_hash(g, hash);
	free_t_hash(&hash);
	free(g->input_msg);
}

void	append_to_msg(t_global *g, void *block, t_fd_iterator *fd_iterator)
{
	char					*temp;
	unsigned long long int	prev_len;

	temp = (char*)malloc(sizeof(char) * fd_iterator->total_len + 1);
	prev_len = fd_iterator->total_len - fd_iterator->last_block_len;
	if (prev_len)
	{
		ft_memcpy(temp, g->input_msg, prev_len);
		free(g->input_msg);
	}
	ft_memcpy(&(temp[prev_len]), block, fd_iterator->last_block_len);
	temp[fd_iterator->total_len] = '\0';
	g->input_msg = temp;
}
