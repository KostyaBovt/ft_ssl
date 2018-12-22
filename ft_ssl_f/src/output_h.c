#include "../includes/ft_ssl.h"

void output_hash(t_global *g, t_hash *hash)
{
	if (!g->q && !g->r)
	{
		ft_printf("%s (", g->alg_print);
		if (g->input_type == 's' || g->input_type == 'i')
			ft_printf("\"");	
		ft_printf("%s", g->input_msg);
		if (g->input_type == 's' || g->input_type == 'i')
			ft_printf("\"");	
		ft_printf(") = ");
	}
	output_the_hash(g, hash);
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

void output_the_hash(t_global *g, t_hash *hash)
{
	int i;

	if (!ft_strcmp(g->alg, "sha256"))
	{
		i = -1;
		while(++i < hash->len)
			ft_printf("%x", (hash->hash)[i]);
	}
	if (!ft_strcmp(g->alg, "md5"))
	{
		i = -1;
		while(++i < (hash->len * 4))
			print_hash_hex(((unsigned char*)hash->hash)[i]);
	}	
}

void		print_hash_hex(unsigned char c)
{
	int		num;
	char	print;

	num = (int)c;
	print = (num / 16) % 16 + ((num / 16 % 16 > 9) ? (-10 + 'a') : '0');
	write(1, &print, 1);
	print = num % 16 + ((num % 16 > 9) ? (-10 + 'a') : '0');
	write(1, &print, 1);
}