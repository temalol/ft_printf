/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:00:40 by nmustach          #+#    #+#             */
/*   Updated: 2020/01/21 20:16:37 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	u_specifier(t_fs *parsed_flags, va_list argslst)
{
	char	*arg;
	int		i;

	i = 0;
	if (parsed_flags->flag_space > 0 || parsed_flags->flag_plus > 0)
	{
		parsed_flags->flag_space = 0;
		parsed_flags->flag_plus = 0;
	}
	if (parsed_flags->size == L || parsed_flags->size == LL)
		arg = ft_itoa_unsigned_long(va_arg(argslst, unsigned long));
	else if (parsed_flags->size == HH)
		arg = ft_itoa_unsigned_long((unsigned char)va_arg(argslst, int));
	else
		arg = ft_itoa_unsigned_long(va_arg(argslst, unsigned int));
	i = write_arg_with_flags_d_i(arg, parsed_flags);
	free(arg);
	free(parsed_flags);
	return (i);
}

int	p_specifier(t_fs *parsed_flags, va_list argslst)
{
	int		i;
	char	*ret;
	char	*zerocase;
	size_t	arg;

	i = 0;
	arg = va_arg(argslst, size_t);
	if (arg <= 0)
	{
		if (parsed_flags->precision == 0)
			zerocase = "";
		else
			zerocase = "0";
		parsed_flags->flag_oct = '#';
		i += write_arg_with_flags_x_o(zerocase, parsed_flags);
		free(parsed_flags);
		return (i);
	}
	ret = dec_to_base(arg, 16, 'x');
	parsed_flags->flag_oct = '#';
	i = write_arg_with_flags_x_o(ret, parsed_flags);
	free(ret);
	free(parsed_flags);
	return (i);
}

int	d_specifier(t_fs *parsed_flags, va_list arglist)
{
	int		i;
	char	*arg;

	if (parsed_flags->size == L || parsed_flags->size == LL)
		arg = ft_itoa_long(va_arg(arglist, long));
	else if (parsed_flags->size == HH)
		arg = ft_itoa_long((char)va_arg(arglist, int));
	else if (parsed_flags->size == H)
		arg = ft_itoa_long((short int)va_arg(arglist, int));
	else
		arg = ft_itoa_long(va_arg(arglist, int));
	i = write_arg_with_flags_d_i(arg, parsed_flags);
	free(parsed_flags);
	free(arg);
	return (i);
}

int	s_specifier(t_fs *parsed_flags, va_list argslist)
{
	char	*arg;
	int		i;

	arg = va_arg(argslist, char*);
	if (arg == 0)
	{
		i = write_arg_with_flags_s("(null)", parsed_flags);
		free(parsed_flags);
		return (i);
	}
	i = write_arg_with_flags_s(arg, parsed_flags);
	free(parsed_flags);
	return (i);
}

int	output_arg(t_fs *parsed_flags, va_list argslst)
{
	if (parsed_flags->type == 's')
		return (s_specifier(parsed_flags, argslst));
	if (parsed_flags->type == 'd' || parsed_flags->type == 'i')
		return (d_specifier(parsed_flags, argslst));
	if (parsed_flags->type == 'p')
		return (p_specifier(parsed_flags, argslst));
	if (parsed_flags->type == 'u')
		return (u_specifier(parsed_flags, argslst));
	if (parsed_flags->type == 'c')
		return (c_specifier(parsed_flags, argslst));
	if (parsed_flags->type == 'x' || parsed_flags->type == 'X')
		return (x_specifier(parsed_flags, argslst));
	if (parsed_flags->type == 'o')
		return (o_specifier(parsed_flags, argslst));
	if (parsed_flags->type == '%')
		return (pct_specifier(parsed_flags, argslst));
	if (parsed_flags->type == 'f')
		return (f_specifier(parsed_flags, argslst));
	if (parsed_flags->type == 'b')
		return (b_specifier(parsed_flags, argslst));
	if (parsed_flags->type == 'y')
		return (y_specifier(parsed_flags, argslst));
	if (parsed_flags->type == 'r')
		return (r_specifier(argslst));
	return (0);
}
