/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_arg_with_flags_d_i.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 20:54:19 by nmustach          #+#    #+#             */
/*   Updated: 2020/01/20 21:48:16 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		write_arg_d(char *arg, t_fs *parsed_flags, int arglen)
{
	int i;

	i = 0;
	if (parsed_flags->flag_space == ' ')
	{
		i += write_space_flag();
		arglen--;
	}
	if (parsed_flags->argsign > 0)
	{
		i += write_sign(parsed_flags->argsign);
		arglen--;
	}
	i += write_precision(arglen - ft_strlen(arg));
	if (arglen > 0)
		i += write_arg_(arg);
	return (i);
}

int		get_arg_len(char *arg, t_fs *parsed_flags)
{
	int len;

	len = 0;
	if (arg[0] == '0' && parsed_flags->precision == 0
	&& parsed_flags->argsign == '+')
		return (1);
	if (arg[0] == '0' && parsed_flags->precision == 0)
		return (0);
	len = ft_strlen(arg);
	if (parsed_flags->argsign > 0)
		len++;
	if (parsed_flags->flag_space > 0)
		len++;
	if (parsed_flags->flag_zero == '0')
		if (parsed_flags->width > len)
			len += parsed_flags->width - len;
	if (parsed_flags->precision >= 0 &&
	parsed_flags->precision > (int)ft_strlen(arg))
		if (parsed_flags->precision - ft_strlen(arg) > 0)
			len += parsed_flags->precision - ft_strlen(arg);
	return (len);
}

void	remove_ignored_flags(t_fs *parsed_flags)
{
	if (parsed_flags->flag_space == ' ' &&
	(parsed_flags->flag_plus == '+' || parsed_flags->argsign == '-'))
		parsed_flags->flag_space = 0;
	if (parsed_flags->argsign == '-' && parsed_flags->flag_plus == '+')
		parsed_flags->flag_plus = 0;
	if ((parsed_flags->precision >= 0 || parsed_flags->flag_minus == '-')
	&& parsed_flags->flag_zero == '0')
		parsed_flags->flag_zero = 0;
	if (parsed_flags->argsign != '-' && parsed_flags->flag_plus == '+')
		parsed_flags->argsign = '+';
}

int		write_arg_with_flags_d_i(char *arg, t_fs *parsed_flags)
{
	int	i;
	int	arglen;

	i = 0;
	if (arg[0] == '-')
	{
		arg++;
		parsed_flags->argsign = '-';
	}
	remove_ignored_flags(parsed_flags);
	arglen = get_arg_len(arg, parsed_flags);
	if (parsed_flags->flag_minus != '-')
		i += write_width_s(parsed_flags->width - arglen, 0);
	i += write_arg_d(arg, parsed_flags, arglen);
	if (parsed_flags->flag_minus == '-')
		i += write_width_s(parsed_flags->width - arglen, 0);
	return (i);
}
