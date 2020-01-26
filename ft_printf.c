/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 19:59:54 by nmustach          #+#    #+#             */
/*   Updated: 2020/01/20 21:32:06 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		validate_flags(t_fs *parsed_flags)
{
	if (!is_type(parsed_flags->type))
	{
		free(parsed_flags);
		return (0);
	}
	return (1);
}

void	write_between_specificators(char *format, int *i, int *ret)
{
	if (format[*i] != '%' && format[*i])
	{
		write(1, &format[*i], 1);
		*i = *i + 1;
		*ret = *ret + 1;
	}
}

void	check_double_percent(char *format, int *i, int *ret)
{
	if (format[*i] == '%' && format[*i + 1] == '%')
	{
		write(1, &format[*i], 1);
		*i += 2;
		*ret = *ret + 1;
	}
}

int		ft_printf(char *format, ...)
{
	int		i;
	int		ret;
	t_fs	*parsed_flags;
	va_list argslst;

	i = 0;
	ret = 0;
	va_start(argslst, format);
	while (format[i])
	{
		if (format[i] == '%' && !format[i + 1])
			return (0);
		if (format[i] == '%' && format[i + 1] != '%')
		{
			parsed_flags = parse_format_string(&format[i + 1], argslst);
			i += parsed_flags->index;
			if (!validate_flags(parsed_flags))
				return (0);
			ret += output_arg(parsed_flags, argslst);
		}
		check_double_percent(format, &i, &ret);
		write_between_specificators(format, &i, &ret);
	}
	va_end(argslst);
	return (ret);
}
