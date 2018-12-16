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
	int					str_len;
	int					str_i;
	int					full_blocks_n;
	int					full_blocks_returned;
	int					last_block_len;
	int					last_blocks_n;
	int					last_blocks_returned;
	void				*(*next)(void *self);
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
int				main(int argc, char **argv);

/*
**global.c
*/
t_global		*init_global(int argc, char **argv);

/*
**hash.c
*/
void			calculate_block_hash(t_ctx *ctx, void *block);
char			*compile_hash(t_ctx *ctx);
uint32_t		*devide_block(void *block);
int				get_word_i(int i);
void			print_block(uint32_t *block);

/*
**main_controller.c
*/
void			call_main_controller(t_global *global);
void			process_av(t_global *g, char *av);
void			add_flag(t_global *g, char *flag);


/*
**padding.c
*/
void			*make_last_padded_block(int msg_len);
void			*make_padded_block(void *block_start, int last_block_len, int msg_len);

/*
**print.c
*/
void			print_erorr_s();
void			print_erorr_file(char *file);
void			print_erorr_command(char *command);
void			print_usage_md5();
void			print_usage_ssl();

/*
**check.c
*/
void			check_command();

/*
**context.c
*/
t_ctx			*init_ctx();
t_ctx			*copy_ctx(t_ctx *ctx);
void			print_ctx(t_ctx *ctx);
void			merge_ctx(t_ctx *ctx, t_ctx *temp_ctx);

/*
**stdin.c
*/
void			process_stdin(t_global *g);

/*
**string.c
*/
void			process_string(t_global *g);
char			*make_hash_string(char *str);
t_str_iterator	*init_str_iterator(char *str);
void			*next_block_str(void *self);

/*
**fghi.c
*/
uint32_t		md5_F(t_ctx *ctx);
uint32_t		md5_G(t_ctx *ctx);
uint32_t		md5_H(t_ctx *ctx);
uint32_t		md5_I(t_ctx *ctx);


/*
**file.c
*/
void			process_file(t_global *g, char *file);

#endif
