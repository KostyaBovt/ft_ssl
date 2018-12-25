/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_h.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbovt <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 18:22:47 by kbovt             #+#    #+#             */
/*   Updated: 2018/12/24 18:22:49 by kbovt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

void	output_hash(t_global *g, t_hash *hash)
{
	if (g->input_type == 'i')
		return (output_hash_stdin(g, hash));
	if (g->r)
		return (output_hash_rev(g, hash));
	else
		return (output_hash_orig(g, hash));
}

void	output_hash_orig(t_global *g, t_hash *hash)
{
	if (!g->q)
	{
		if (g->input_type == 'i' || g->input_type == 's')
			ft_printf("%s (\"%s\") = ", g->alg_print, g->input_msg);
		else
			ft_printf("%s (%s) = ", g->alg_print, g->input_msg);
	}
	output_the_hash(g, hash);
	ft_printf("\n");
}

void	output_hash_rev(t_global *g, t_hash *hash)
{
	output_the_hash(g, hash);
	if (!g->q)
	{
		if (g->input_type == 'i' || g->input_type == 's')
			ft_printf(" \"%s\"", g->input_msg);
		else
			ft_printf(" %s", g->input_msg);
	}
	ft_printf("\n");
}

void	output_hash_stdin(t_global *g, t_hash *hash)
{
	if (g->input_was)
		ft_printf("%s", g->input_msg);
	output_the_hash(g, hash);
	ft_printf("\n");
}

void	output_the_hash(t_global *g, t_hash *hash)
{
	int	i;

	if (!ft_strcmp(g->alg, "sha256"))
	{
		i = -1;
		while (++i < hash->len)
			ft_printf("%x", (hash->hash)[i]);
	}
	if (!ft_strcmp(g->alg, "md5"))
	{
		i = -1;
		while (++i < (hash->len * 4))
			print_hash_hex(((unsigned char*)hash->hash)[i]);
	}
}
