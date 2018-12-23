#ifndef SSL_H
# define SSL_H

# include "../../libft/includes/libft.h"
# include "../../printf/includes/ft_printf.h"
# include <unistd.h> // close write
# include <fcntl.h> // open
# include <stdlib.h> // malloc free
# include <stdio.h> // printf


typedef struct			s_hash
{
	uint32_t			*hash;
	int					len;
}						t_hash;

typedef struct			s_global
{
	char				*alg;
	char				*alg_print;
	int					ac;
	char				**av;
	char				r;
	char				q;
	int					av_i;
	char				reach_files;
	char				input_was;
	char				*input_msg;
	char				input_type;
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
	char				malloced;
	void				*(*next)(void *self);
	t_global 			*g;
}						t_str_iterator;


typedef struct			s_fd_iterator
{
	char				*file;
	int					fd;
	unsigned long long int	total_len;
	int					full_blocks_n;
	int					full_blocks_returned;
	int					last_block_len;
	int					last_blocks_n;
	int					last_blocks_returned;
	void				*(*next)(void *self);
	t_global 			*g;
}						t_fd_iterator;


typedef struct			s_ctx
{
	uint32_t			a;
	uint32_t			b;
	uint32_t			c;
	uint32_t			d;
	uint32_t			h0;
	uint32_t			h1;
	uint32_t			h2;
	uint32_t			h3;
	uint32_t			h4;
	uint32_t			h5;
	uint32_t			h6;
	uint32_t			h7;
}						t_ctx;


/*
**bitwise.c
*/
uint32_t		ft_rotr(uint32_t n, int shift);

/*
**check.c
*/
void			check_command(t_global *g);

/*
**context.c
*/
t_ctx			*init_ctx();
t_ctx			*copy_ctx(t_ctx *ctx);
void			print_ctx(t_ctx *ctx);
void			merge_ctx(t_ctx *ctx, t_ctx *temp_ctx);
void			print_ctx_hex(t_ctx *ctx);

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
t_fd_iterator	*init_fd_iterator(t_global *g, int fd);
void			*next_block_fd(void *self_void);

/*
**global.c
*/
t_global		*init_global(int argc, char **argv);

/*
**hash.c
*/
void			calculate_block_hash(t_global *g, t_ctx *ctx, void *block);
t_hash			*compile_hash(t_global *g, t_ctx *ctx);

/*
**hash_md5.c
*/
void			calc_block_hash_md5(t_ctx *ctx, void *block);
t_hash			*compile_hash_md5(t_ctx *ctx);
uint32_t		*devide_block_md5(void *block);
int				get_word_i(int i);
void			print_block(uint32_t *block);

/*
**hash_sha256.c
*/
void			calc_block_hash_sha256(t_ctx *ctx, void *block);
uint32_t		*devide_block_sha256(void *block);
t_hash			*compile_hash_sha256(t_ctx *ctx);
void			print_block_sha256(uint32_t *block);

/*
**kill_leaks.c
*/
void			free_t_global(t_global **g_p);
void			free_t_hash(t_hash **hash);

/*
**main.c
*/
int				main(int argc, char **argv);

/*
**main_controller.c
*/
void			call_main_controller(t_global *global);
void			process_av(t_global *g, char *av);
void			add_flag(t_global *g, char *flag);

/*
**output_h.c
*/
void			output_hash(t_global *g, t_hash *hash);
void			output_the_hash(t_global *g, t_hash *hash);
void			print_hash_hex(unsigned char c);

/*
**padding.c
*/
void			*make_last_padded_block(t_global *g, unsigned long long int msg_len);
void			*make_padded_block(t_global *g, void *block_start, int last_block_len, unsigned long long int msg_len);
void			ft_memcpy_rot(void *dst, const void *src, size_t n);

/*
**print.c
*/
void			print_erorr_s();
void			print_erorr_file(char *file);
void			print_erorr_command(char *command);
void			print_usage_command(char *command);
void			print_usage_ssl();

/*
**stdin.c
*/
void			process_stdin(t_global *g);
void			append_to_msg(t_global *g, void *block, t_fd_iterator *fd_iterator);

/*
**string.c
*/
void			process_string(t_global *g);
t_hash			*make_hash_string(t_global *g, char *str);
t_str_iterator	*init_str_iterator(t_global *g, char *str);
void			*next_block_str(void *self);


#endif
