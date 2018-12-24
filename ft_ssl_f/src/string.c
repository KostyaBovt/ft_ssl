/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbovt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 18:23:29 by kbovt             #+#    #+#             */
/*   Updated: 2018/12/24 18:23:31 by kbovt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void			process_string(t_global *g)
{
	t_hash	*hash;

	g->input_was = 1;
	if (g->ac - 1 == g->av_i)
	{
		print_erorr_s();
		print_usage_command(g->alg);
		exit(EXIT_SUCCESS);
	}
	else
	{
		(g->av_i)++;
		g->input_msg = g->av[g->av_i];
		g->input_type = 's';
		hash = make_hash_string(g, g->av[g->av_i]);
		output_hash(g, hash);
		free_t_hash(&hash);
	}
}

t_hash			*make_hash_string(t_global *g, char *str)
{
	t_ctx			*ctx;
	void			*block;
	t_str_iterator	*str_iterator;
	t_hash			*hash;

	ctx = init_ctx();
	str_iterator = init_str_iterator(g, str);
	while ((block = str_iterator->next((void*)str_iterator)))
	{
		calculate_block_hash(g, ctx, block);
		if (str_iterator->malloced)
			free(block);
	}
	free(str_iterator);
	hash = compile_hash(g, ctx);
	free(ctx);
	return (hash);
}

t_str_iterator	*init_str_iterator(t_global *g, char *str)
{
	t_str_iterator	*new;

	new = (t_str_iterator*)malloc(sizeof(t_str_iterator));
	new->str = str;
	new->str_len = ft_strlen(str);
	new->str_i = 0;
	new->full_blocks_n = new->str_len / 64;
	new->full_blocks_returned = 0;
	new->last_block_len = new->str_len % 64;
	new->last_blocks_n = new->last_block_len < 56 ? 1 : 2;
	new->last_blocks_returned = 0;
	new->malloced = 0;
	new->next = &next_block_str;
	new->g = g;
	return (new);
}

void			*next_block_str(void *self_void)
{
	void			*final_block;
	t_str_iterator	*self;

	self = (t_str_iterator*)self_void;
	if (self->full_blocks_returned < self->full_blocks_n)
	{
		final_block = (void*)(&(self->str[self->str_i]));
		(self->full_blocks_returned)++;
		self->str_i += 64;
		return (final_block);
	}
	else if (self->last_blocks_returned < self->last_blocks_n)
	{
		if (self->last_blocks_returned == 1)
			final_block = make_last_padded_block(self->g, self->str_len);
		else
			final_block = make_padded_block(self->g, \
			(void*)(&(self->str[self->str_i])), \
			self->last_block_len, self->str_len);
		(self->last_blocks_returned)++;
		self->malloced = 1;
		return (final_block);
	}
	else
		return (NULL);
}
