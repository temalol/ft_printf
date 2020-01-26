/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_to_str2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:38:19 by nmustach          #+#    #+#             */
/*   Updated: 2020/01/21 19:33:34 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			write_arg_with_flags_f(char *before,
char *after, t_fs *parsed_flags)
{
	int i;
	int arglen;

	i = 0;
	remove_ignored_flags_f(parsed_flags);
	arglen = calc_arg_len_f(before, after, parsed_flags);
	if (parsed_flags->flag_minus != '-')
		i += write_width_s(parsed_flags->width - arglen, 0);
	i += write_f(before, after, parsed_flags, arglen);
	if (parsed_flags->flag_minus == '-')
		i += write_width_s(parsed_flags->width - arglen, 0);
	return (i);
}

long double	round_f(long double f, int precision)
{
	f += 0.5 * get_rounding_coeff(precision);
	return (f);
}

char		*get_num_before_point(long double f)
{
	return (ft_itoa_long((long long)f));
}

void		write_sign_f(t_fs *parsed_flags, int *arglen, int *i)
{
	if (parsed_flags->flag_space == ' ')
	{
		*i += write_arg_(" ");
		*arglen = *arglen - 1;
	}
	if (parsed_flags->argsign == '-' && parsed_flags->flag_plus == 0)
	{
		*i += write_arg_("-");
		*arglen = *arglen - 1;
	}
	if (parsed_flags->flag_plus > 0)
	{
		*i += write_arg_("+");
		*arglen = *arglen - 1;
	}
}
