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
	int					ac;
	char				**av;
	char				r;
	char				q;
	int					av_i;
	char				reach_files;
	char				input_was;
	char				*mock;
}						t_global;


typedef struct			s_str_iterator
{
	char				*str;
	int					str_i;
	int					str_len;
	int					str_i;
	void				*(*next_block_str)(void *self);
}						t_str_iterator;


typedef struct			s_ctx
{
	uint32_t			a;
	uint32_t			b;
	uint32_t			c;
	uint32_t			d;
}						t_ctx;



/*
**main.c
*/
int			main(int argc, char **argv);

/*
**global.c
*/
t_global	*init_global(int argc, char **argv);


/*
**main_controller.c
*/
void		call_main_controller(t_global *global);
void		process_av(t_global *g, char *av);
void		add_flag(t_global *g, char *flag);

/*
**print.c
*/
void		print_erorr_s();
void		print_erorr_command(char *command);
void		print_usage_md5();
void		print_usage_ssl();

/*
**check.c
*/
void		check_command();


/*
**stdin.c
*/
void		process_stdin(t_global *g);

/*
**string.c
*/
void		process_string(t_global *g);

/*
**file.c
*/
void		process_file(t_global *g, char *file);

#endif
