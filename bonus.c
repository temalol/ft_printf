/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 01:44:10 by nmustach          #+#    #+#             */
/*   Updated: 2020/01/21 20:18:23 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_arg_y(char *arg, t_fs *parsed_flags, int arrlen)
{
	int i;

	i = 0;
	if (parsed_flags->flag_oct > 0)
	{
		write(1, "[", 1);
		i++;
	}
	i += write_arg_(arg);
	if (parsed_flags->flag_oct > 0)
	{
		write(1, "]", 1);
		i++;
	}
	if (arrlen >= 1 && parsed_flags->flag_space > 0)
		write(1, " ", 1);
	return (i);
}

int	r_specifier(va_list argslst)
{
	int i;
	int arg;

	i = 0;
	arg = va_arg(argslst, int);
	if (arg > 31)
		return (0);
	if (arg >= 16)
	{
		arg = arg - 16;
		arg = arg * 3;
		while (i < 3 && NON_PRT1[arg] > 32)
		{
			write(1, &NON_PRT1[arg++], 1);
			i++;
		}
		return (i);
	}
	arg = arg * 3;
	while (i < 3 && NON_PRT0[arg] > 32)
	{
		write(1, &NON_PRT0[arg++], 1);
		i++;
	}
	return (i);
}

int	y_specifier(t_fs *parsed_flags, va_list argslst)
{
	int		arrlen;
	int		*arr;
	char	*arg;
	int		ret;

	ret = 0;
	arr = va_arg(argslst, int*);
	arrlen = va_arg(argslst, int);
	if (arrlen >= 0)
		while (arrlen--)
		{
			arg = ft_itoa_long(*arr);
			ret += write_arg_y(arg, parsed_flags, arrlen);
			free(arg);
			arr++;
		}
	return (ret);
}

int	b_specifier(t_fs *parsed_flags, va_list argslst)
{
	int		i;
	char	*arg;

	arg = dec_to_base(va_arg(argslst, size_t), 2, 'b');
	i = write_arg_with_flags_s(arg, parsed_flags);
	free(parsed_flags);
	free(arg);
	return (i);
}

int	get_preambula_len(t_fs *parsed_flags, char *arg)
{
	int len;

	len = 0;
	if (parsed_flags->type == 'p' && arg[0] == '0')
		len += 2;
	if (parsed_flags->flag_oct > 0 && arg[0] != '0')
	{
		if (parsed_flags->type == 'x' || parsed_flags->type == 'X'
		|| parsed_flags->type == 'p')
			len += 2;
		else
			len++;
	}
	return (len);
}
