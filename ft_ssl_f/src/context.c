#include "../includes/ft_ssl.h"

t_ctx *init_ctx()
{
	new *t_ctx;

	new = (t_ctx*)malloc(sizeof(t_ctx));
	new->a = 0x67452301;
	new->b = 0xefcdab89;
	new->c = 0x98badcfe;
	new->d = 0x10325476;
	return new;
}