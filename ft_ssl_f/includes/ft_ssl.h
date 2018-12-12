#ifndef SSL_H
# define SSL_H

# include "../../libft/includes/libft.h"
# include "../../printf/includes/ft_printf.h"
# include <unistd.h> // close write
# include <fcntl.h> // open
# include <stdlib.h> // malloc free
# include <stdio.h> // printf

typedef struct			s_global
{
	int					argc;
	char				**argv;
}						t_global;

/*
**main.c
*/
int main(int argc, char **argv);

/*
**global.c
*/
t_global *init_global(int argc, char **argv);


#endif
