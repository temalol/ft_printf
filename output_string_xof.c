/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_string_xof.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:02:37 by nmustach          #+#    #+#             */
/*   Updated: 2020/01/20 21:17:21 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	f_specifier(t_fs *parsed_flags, va_list argslst)
{
	char			*before;
	char			*after;
	long double		f;
	int				i;

	if (parsed_flags->precision < 0)
		parsed_flags->precision = 6;
	if (parsed_flags->size == LF)
		f = va_arg(argslst, long double);
	else
		f = va_arg(argslst, double);
	if (f < 0)
	{
		f *= -1;
		parsed_flags->argsign = '-';
		parsed_flags->flag_plus = 0;
	}
	f = round_f(f, parsed_flags->precision);
	before = get_num_before_point(f);
	after = get_num_after_point(f, parsed_flags->precision);
	i = write_arg_with_flags_f(before, after, parsed_flags);
	free(parsed_flags);
	free(before);
	free(after);
	return (i);
}

int	pct_specifier(t_fs *parsed_flags, va_list argslst)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	(void)(argslst);
	if (parsed_flags->flag_minus == '-')
	{
		write(1, "%", 1);
		i++;
		i += write_width_s(parsed_flags->width - 1, 0);
		return (i);
	}
	if (parsed_flags->width > 0)
	{
		if (parsed_flags->flag_zero == '0')
			flag = 1;
		i += write_width_s(parsed_flags->width - 1, flag);
		write(1, "%", 1);
		i++;
		return (i);
	}
	write(1, "%", 1);
	return (1);
}

int	o_specifier(t_fs *parsed_flags, va_list argslst)
{
	char	*oct;
	int		i;

	i = 0;
	if (parsed_flags->size == HH)
		oct = dec_to_base((unsigned char)va_arg(argslst, int), 8, 'o');
	else if (parsed_flags->size == H)
		oct = dec_to_base_unsigned_long((short unsigned int)va_arg(argslst,
		int), 8, 'o');
	else if (parsed_flags->size == L || parsed_flags->size == LL)
		oct = dec_to_base(va_arg(argslst, size_t), 8, 'o');
	else
		oct = dec_to_base(va_arg(argslst, unsigned int), 8, 'o');
	i = write_arg_with_flags_x_o(oct, parsed_flags);
	free(parsed_flags);
	free(oct);
	return (i);
}

int	x_specifier(t_fs *parsed_flags, va_list argslst)
{
	char	*hex;
	int		i;

	if (parsed_flags->size == L || parsed_flags->size == LL)
		hex = dec_to_base_unsigned_long(va_arg(argslst,
		unsigned long), 16, parsed_flags->type);
	else if (parsed_flags->size == HH)
		hex = dec_to_base((unsigned char)va_arg(argslst,
		int), 16, parsed_flags->type);
	else if (parsed_flags->size == H)
		hex = dec_to_base_unsigned_long((short unsigned int)va_arg(argslst,
		int), 16, parsed_flags->type);
	else
		hex = dec_to_base(va_arg(argslst,
		unsigned int), 16, parsed_flags->type);
	i = write_arg_with_flags_x_o(hex, parsed_flags);
	free(parsed_flags);
	free(hex);
	return (i);
}

int	c_specifier(t_fs *parsed_flags, va_list argslst)
{
	int		i;
	char	arg[2];

	arg[0] = va_arg(argslst, int);
	arg[1] = '\0';
	if (arg[0] != 0)
		i = write_arg_with_flags_s(arg, parsed_flags);
	else
	{
		if (parsed_flags->flag_minus == '-')
		{
			write(1, "\0", 1);
			i = write_width_s(parsed_flags->width - 1, 0);
		}
		if (parsed_flags->flag_minus != '-')
		{
			i = write_width_s(parsed_flags->width - 1, 0);
			write(1, "\0", 1);
		}
		i += 1;
	}
	free(parsed_flags);
	return (i);
}
