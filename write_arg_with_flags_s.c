/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_arg_with_flags_s.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 18:35:57 by nmustach          #+#    #+#             */
/*   Updated: 2020/01/20 19:08:24 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			write_width_s(int widthlen, int zero_flag)
{
	char	c;
	int		ret;

	ret = 0;
	c = ' ';
	if (zero_flag == 1)
		c = '0';
	if (widthlen > 0)
		while (widthlen--)
		{
			write(1, &c, 1);
			ret++;
		}
	return (ret);
}

static int	write_arg_s(char *arg, int precision)
{
	int i;

	i = 0;
	if (precision < 0)
	{
		while (arg[i])
		{
			write(1, &arg[i], 1);
			i++;
		}
	}
	else
	{
		while (arg[i] && precision)
		{
			write(1, &arg[i], 1);
			i++;
			precision--;
		}
	}
	return (i);
}

static int	calc_width_s(char *arg, t_fs *parsed_flags)
{
	int width;
	int arglen;

	arglen = ft_strlen(arg);
	if (parsed_flags->precision >= 0
	&& parsed_flags->precision < (int)ft_strlen(arg))
		arglen = parsed_flags->precision;
	width = parsed_flags->width - arglen;
	return (width);
}

int			write_arg_with_flags_s(char *arg, t_fs *parsed_flags)
{
	int i;

	i = 0;
	if (parsed_flags->flag_minus == '-')
	{
		i += write_arg_s(arg, parsed_flags->precision);
		i += write_width_s(calc_width_s(arg, parsed_flags), 0);
		return (i);
	}
	if (parsed_flags->width > 0)
	{
		i += write_width_s(calc_width_s(arg, parsed_flags), 0);
		i += write_arg_s(arg, parsed_flags->precision);
		return (i);
	}
	i += write_arg_s(arg, parsed_flags->precision);
	return (i);
}
