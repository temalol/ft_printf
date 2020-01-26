/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_arg_with_flags_h_o.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 18:48:07 by nmustach          #+#    #+#             */
/*   Updated: 2020/01/21 18:13:47 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		write_sign_x_o(char signcase)
{
	if (signcase == 'X')
	{
		write(1, "0X", 2);
		return (2);
	}
	if (signcase == 'o' || signcase == 'O')
	{
		write(1, "0", 1);
		return (1);
	}
	write(1, "0x", 2);
	return (2);
}

int		write_arg_x_o(char *arg, t_fs *parsed_flags, int arglen)
{
	int i;

	i = 0;
	if (parsed_flags->flag_oct > 0)
	{
		i += write_sign_x_o(parsed_flags->type);
		if (parsed_flags->type == 'x' || parsed_flags->type == 'X'
		|| parsed_flags->type == 'p')
			arglen -= 2;
		else
			arglen--;
	}
	i += write_precision(arglen - ft_strlen(arg));
	if (arglen > 0)
		i += write_arg_(arg);
	return (i);
}

void	remove_igonred_flags_x_o(t_fs *parsed_flags)
{
	if ((parsed_flags->precision >= 0 || parsed_flags->flag_minus == '-')
	&& parsed_flags->flag_zero == '0')
		parsed_flags->flag_zero = 0;
}

int		get_arg_len_x_o(char *arg, t_fs *parsed_flags)
{
	int len;

	len = 0;
	if (arg[0] == '0' && parsed_flags->precision == 0
	&& parsed_flags->flag_oct > 0)
		return (1);
	if (arg[0] == '0' && parsed_flags->precision == 0)
		return (0);
	len = ft_strlen(arg);
	len += get_preambula_len(parsed_flags, arg);
	if (parsed_flags->flag_zero == '0')
		if (parsed_flags->width > len)
			len += parsed_flags->width - len;
	if (parsed_flags->precision >= 0 && parsed_flags->precision > (int)
	ft_strlen(arg) && (parsed_flags->type == 'o' || parsed_flags->type == 'O'))
	{
		if (parsed_flags->precision - len > 0)
			len += parsed_flags->precision - len;
		return (len);
	}
	if (parsed_flags->precision >= 0 &&
	parsed_flags->precision > (int)ft_strlen(arg))
		if (parsed_flags->precision - ft_strlen(arg) > 0)
			len += parsed_flags->precision - ft_strlen(arg);
	return (len);
}

int		write_arg_with_flags_x_o(char *arg, t_fs *parsed_flags)
{
	int i;
	int arglen;

	i = 0;
	if (arg[0] == '0' && parsed_flags->flag_oct > 0 &&
	parsed_flags->type != 'o' && parsed_flags->type != 'O'
	&& parsed_flags->type != 'p')
		parsed_flags->flag_oct = 0;
	remove_igonred_flags_x_o(parsed_flags);
	arglen = get_arg_len_x_o(arg, parsed_flags);
	if (parsed_flags->flag_minus != '-')
		i += write_width_s(parsed_flags->width - arglen, 0);
	i += write_arg_x_o(arg, parsed_flags, arglen);
	if (parsed_flags->flag_minus == '-')
		i += write_width_s(parsed_flags->width - arglen, 0);
	return (i);
}
