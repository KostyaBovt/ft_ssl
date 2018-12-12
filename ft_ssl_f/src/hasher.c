#include "../includes/ft_ssl.h"

void	make_hash(t_global *global)
{
	parse_input(global);
}

void	parse_input(t_global *global)
{
	//parse all argv: 
	// -s flag and get next argv as input string (error if does not exist)
	// -p flag: read stdin and get it as input string (if no stdin - open read from 0 fd)
	// -q flag: just remember if it is
	// -r flag: just remember if it is

	// make 
}