#include "../includes/ft_ssl.h"

void	print_erorr_s()
{
	ft_printf("md5: option requires an argument -- s\n");
}

void	print_erorr_command(char *command)
{
	ft_printf("ft_ssl: Error: '%s' is an invalid command.\n\n", command);
	ft_printf("Standard commands:\n\nMessage Digest commands:\nmd5\nsha256\n\nCipher commands:\n");
}

void	print_usage_md5()
{
	ft_printf("usage: md5 [-pqrtx] [-s string] [files ...]\n");
}

void	print_usage_ssl()
{
	ft_printf("usage: ft_ssl command [command opts] [command args]\n");
}
