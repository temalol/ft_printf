/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:51:32 by nmustach          #+#    #+#             */
/*   Updated: 2020/01/21 20:16:08 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

# define ANSI_RED "\x1b[31m"
# define ANSI_GREEN   "\x1b[32m"
# define ANSI_YELLOW  "\x1b[33m"
# define ANSI_BLUE    "\x1b[34m"
# define ANSI_MAGENTA "\x1b[35m"
# define ANSI_CYAN    "\x1b[36m"
# define ANSI_RESET "\x1b[0m"

# define HH 1
# define LL 4
# define H 2
# define L 3
# define LF 5

# define TYPE "cspdiouxXfb%yr"
# define FLAG "-+ #0"

# define NON_PRT0 "NULSOHSTXETXEOTENQACKBELBS TABLF VT FF CR SO SI "
# define NON_PRT1 "DLEDC1DC2DC3DC4NAKSYNETBCANEM SUBFSCFS GS RS US "

typedef	struct	s_fs
{
	int		index;
	char	flag_oct;
	char	flag_space;
	char	flag_minus;
	char	flag_plus;
	char	flag_zero;
	int		width;
	int		precision;
	int		size;
	char	type;
	char	argsign;
}				t_fs;

int				ft_printf(char *format, ...);
t_fs			*allocate_new_struct(t_fs *new);
t_fs			*parse_format_string(char *format, va_list argslst);
int				parse_width(char *ptr, t_fs *parsed_flags, va_list argslst);
int				parse_precision(char *format,
t_fs *parsed_flags, va_list argslst);
int				is_flag(char flag_index);
int				is_type(char type);
int				get_size(char *format, t_fs *parsed_flags);
int				output_arg(t_fs *parsed_flags, va_list argslst);
int				s_specifier(t_fs *parsed_flags, va_list argslist);
char			*dec_to_base(size_t n, int base, char up);
char			*ft_strrev(char *arr);
char			*ft_itoa_long(long n);
char			*ft_itoa_unsigned_long(unsigned long n);
char			*dec_to_base_unsigned_long(unsigned long n, int base, char up);
char			*dec_to_base_short(short unsigned int n, int base, char up);
int				write_arg_with_flags_s(char *arg, t_fs *parsed_flags);
int				write_arg_with_flags_d_i(char *arg, t_fs *parsed_flags);
int				write_width_s(int widthlen, int zero_flag);
int				write_arg_with_flags_x_o(char *arg, t_fs *parsed_flags);
int				write_precision(int len);
int				write_arg_(char *arg);
int				write_sign(char c);
int				write_space_flag(void);
void			remove_ignored_flags(t_fs *parsed_flags);
char			*get_num_before_point(long double f);
long double		round_f(long double f, int precision);
char			*get_num_after_point(long double f,
int precision);
int				write_arg_with_flags_f(char *before,
char *after, t_fs *parsed_flags);
int				write_arg_y(char *arg, t_fs *parsed_flags, int arrlen);
int				r_specifier(va_list argslst);
int				c_specifier(t_fs *parsed_flags, va_list argslst);
int				x_specifier(t_fs *parsed_flags, va_list argslst);
int				o_specifier(t_fs *parsed_flags, va_list argslst);
int				pct_specifier(t_fs *parsed_flags, va_list argslst);
int				f_specifier(t_fs *parsed_flags, va_list argslst);
int				y_specifier(t_fs *parsed_flags, va_list argslst);
int				b_specifier(t_fs *parsed_flags, va_list argslst);
void			remove_ignored_flags_f(t_fs
*parsed_flags);
int				calc_arg_len_f(char *before,
char *after, t_fs *parsed_flags);
int				write_f(char *before, char *after,
t_fs *parsed_flags, int arglen);
long double		get_rounding_coeff(int precision);
void			write_sign_f(t_fs *parsed_flags, int *arglen, int *i);
int				get_preambula_len(t_fs *parsed_flags, char *arg);
#endif
