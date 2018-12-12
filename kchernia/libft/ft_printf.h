/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kchernia <kchernia@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 17:33:47 by kchernia          #+#    #+#             */
/*   Updated: 2018/10/19 08:31:00 by kchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <wchar.h>
# include <inttypes.h>

# define IS_PERCENT(X) (X == '%')
# define TO_BINARY(X) (X == 'b')
# define IS_CHAR(X) (X == 'c' || X == 'C')
# define IS_STRING(X) (X == 'S' || X == 's')
# define IS_SIGNED_INT(X) (X == 'd' || X == 'D' || X == 'i')
# define IS_POINTER(X) (X == 'p')
# define TO_HEX(X) (X == 'x' || X == 'X')
# define TO_OCT(X) (X == 'o' || X == 'O')
# define TO_INT(X) (X == 'u' || X == 'U')
# define IS_UINT(X) (TO_HEX(X) || TO_OCT(X) || TO_INT(X) || TO_BINARY(X))
# define IS_FLAG(X) (X == '#' || X == '0' || X == '-' || X == '+' || X == ' ')
# define IS_DIGIT(X) (X >= '0' && X <= '9')
# define IS_SIZE(X) (X == 'h' || X == 'l' || X == 'j' || X == 'z')
# define IS_STR_TYPE(X) (IS_CHAR(X) || IS_STRING(X))
# define IS_NUM_TYPE(X) (IS_SIGNED_INT(X) || IS_POINTER(X) || IS_UINT(X))
# define IS_TYPE(X) (IS_STR_TYPE(X) || IS_NUM_TYPE(X) || IS_PERCENT(X))
# define MDF_HH	(1)
# define MDF_H	(2)
# define MDF_L	(3)
# define MDF_LL	(4)
# define MDF_J	(5)
# define MDF_Z	(6)

typedef unsigned long long	t_ull;
typedef long long			t_ll;

typedef struct				s_flags
{
	int						hash;
	int						zero;
	int						minus;
	int						plus;
	int						space;
}							t_flags;

typedef struct				s_format
{
	t_flags					flags;

	size_t					width;
	size_t					precision;
	unsigned int			prec;
	int						size;
	char					type;
	char					*arg;
	size_t					arg_index;
	char					*result;
	size_t					result_index;
	size_t					result_size;
	unsigned int			is_ptr;
}							t_format;

int							ft_printf(const char *format, ...);
int							ft_sprintf(char *str, const char *format, ...);
int							ft_vsprintf(char **strp, const char *format,
							va_list *ap);

void						put_frmt_percent(t_format *frmt);
void						put_frmt_char(void *input, t_format *frmt);
void						put_frmt_str(void *input, t_format *frmt);
void						put_frmt_pointer(void *input, t_format *frmt);
void						put_frmt_signed(t_ll num, t_format *frmt);

void						put_frmt_unsigned(t_ull num, t_format *frmt);
void						put_frmt_ui(t_ull num, t_format *frmt);
void						put_frmt_ux(t_ull num, t_format *frmt, int base);
void						put_frmt_uo(t_ull num, t_format *frmt);

void						clean_format(t_format *frmt);
int							get_format(const char **start, const char **cur,
							t_format *frmt, va_list *ap);
void						check_flags(const char **cur, t_format *frmt);
void						check_digit(size_t *dst, const char **cur);
void						move_if(int if_result, int *assign_if,
							int assign_value, char const **to_move);
void						check_size(const char **cur, t_format *frmt);

void						get_arg(va_list *ap, t_format *frmt);

int							ft_putsign(t_format *frmt, t_ll num, size_t i);
size_t						get_index(size_t c1, size_t c2, size_t r1,
							size_t r2);

void						ft_putoxnum(t_format *frmt, t_ull num, int i,
							size_t numlen);
void						get_base_tab(t_format *frmt, char const **tab,
							int *base);
size_t						unumlen_base(t_ull number, int base);
size_t						ft_unumlen(t_ull num);
size_t						get_total_len_ui(t_ull num, t_format *frmt,
							size_t numlen);
void						ft_putunum(t_format *frmt, t_ull num, int i);
void						get_alter_form(t_format *frmt, size_t i1,
							size_t i2);

size_t						ft_oxnumlen(t_ull num, t_format *frmt);
size_t						get_total_len_ux(t_ull num, t_format *frmt,
							size_t *numlen);
size_t						get_total_len_uo(t_ull num, t_format *frmt,
							size_t numlen);
size_t						ft_put_alter_form(t_format *frmt, size_t index);

size_t						ft_strlen(const char *str);
size_t						wchar_size(wchar_t c);
void						write_wsize_chars(char *s, size_t i,
							size_t wsize, wchar_t c);
wchar_t						*wstrnew(size_t size, wchar_t c);
void						widestrtostrn(wchar_t const *ws, char *s, size_t n);
void						strtowidestrn(char const *s, wchar_t *ws, size_t n);
size_t						widestrtostrlen(wchar_t const *str,
							size_t precision);

char						*stralloc_and_fill(size_t size, char c);
void						add_to_result(t_format *frmt,
							const char *src, size_t n);

#endif
