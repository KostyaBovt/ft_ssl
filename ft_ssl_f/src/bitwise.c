#include "../includes/ft_ssl.h"

uint32_t ft_rotr(uint32_t n, int shift)
{
	return (n >> shift) | (n << (32 - shift));
}