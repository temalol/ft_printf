/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_to_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/24 19:15:25 by nmustach          #+#    #+#             */
/*   Updated: 2020/01/21 18:04:14 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		remove_ignored_flags_f(t_fs *parsed_flags)
{
	if (parsed_flags->flag_space == ' ' && (parsed_flags->flag_plus == '+'
	|| parsed_flags->argsign == '-'))
		parsed_flags->flag_space = 0;
	if (parsed_flags->argsign == '-' && parsed_flags->flag_plus == '+')
		parsed_flags->flag_plus = 0;
	if (parsed_flags->argsign != '-' && parsed_flags->flag_plus == '+')
		parsed_flags->argsign = '+';
	if (parsed_flags->flag_zero > 0 && parsed_flags->flag_minus > 0)
		parsed_flags->flag_zero = 0;
}

int			write_f(char *before, char *after, t_fs *parsed_flags, int arglen)
{
	int i;

	i = 0;
	write_sign_f(parsed_flags, &arglen, &i);
	if (parsed_flags->precision > 0 || (parsed_flags->precision == 0
	&& parsed_flags->flag_oct > 0))
		i += write_precision(arglen - ft_strlen(before) - ft_strlen(after) - 1);
	else
		i += write_precision(arglen - ft_strlen(before) - ft_strlen(after));
	i += write_arg_(before);
	if (parsed_flags->precision > 0 || (parsed_flags->precision == 0
	&& parsed_flags->flag_oct > 0))
		i += write_arg_(".");
	i += write_arg_(after);
	return (i);
}

int			calc_arg_len_f(char *before, char *after, t_fs *parsed_flags)
{
	int len;

	len = 0;
	len += ft_strlen(before) + ft_strlen(after);
	if (parsed_flags->argsign > 0)
		len++;
	if (parsed_flags->precision > 0 || (parsed_flags->precision == 0
	&& parsed_flags->flag_oct > 0))
		len++;
	if (parsed_flags->flag_plus > 0 && parsed_flags->argsign == 0)
		len++;
	if (parsed_flags->flag_space > 0)
		len++;
	if (parsed_flags->flag_zero > 0)
		if (parsed_flags->width - len > 0)
			len += parsed_flags->width - len;
	return (len);
}

long double	get_rounding_coeff(int precision)
{
	long double coeff;

	coeff = 1;
	while (precision)
	{
		coeff /= 10;
		precision--;
	}
	return (coeff);
}

char		*get_num_after_point(long double f, int precision)
{
	size_t	tmp;
	char	*after;
	int		i;
	int		prec;

	i = 0;
	prec = precision;
	after = malloc((sizeof(char) * precision) + 1);
	while (precision)
	{
		f = f - (size_t)f;
		if (precision == 1 && prec >= 20)
			f += 0.05;
		f *= 10.0;
		tmp = (size_t)f;
		after[i] = tmp % 10 + '0';
		i++;
		precision--;
	}
	after[i] = '\0';
	return (after);
}
