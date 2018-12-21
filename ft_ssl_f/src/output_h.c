#include "../includes/ft_ssl.h"

void output_hash(t_global *g, t_hash *hash)
{
	int i;

	if (!g->q && !g->r)
	{
		ft_printf("%s (", ft_toupper(g->alg));
		if (g->input_type == 's' || g->input_type == 'i')
			ft_printf("\"");	
		ft_printf("%s", g->input_msg);
		if (g->input_type == 's' || g->input_type == 'i')
			ft_printf("\"");	
		ft_printf(") = ");
	}
	i = -1;
	while(++i < hash->len)
		ft_printf("%x", (hash->hash)[i]);
	if (!g->q && !g->r)
			ft_printf("\n");
	if (!g->q && g->r)
	{
		if (g->input_type == 's' || g->input_type == 'i')
			ft_printf("\"");	
		ft_printf("%s", g->input_msg);
		if (g->input_type == 's' || g->input_type == 'i')
			ft_printf("\"\n");
	}
}

void output_the_hash()
{
	
}