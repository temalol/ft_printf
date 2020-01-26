/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:29:07 by nmustach          #+#    #+#             */
/*   Updated: 2020/01/20 21:33:00 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_precision(char *format, t_fs *parsed_flags, va_list argslst)
{
	int res;
	int i;

	i = 0;
	res = 0;
	if (format[i] == '*')
	{
		parsed_flags->precision = va_arg(argslst, int);
		return (2);
	}
	parsed_flags->precision = 0;
	while (ft_isdigit(format[i]))
	{
		res = 10 * res + (format[i] - '0');
		i++;
	}
	parsed_flags->precision = res;
	return (i + 1);
}

int		parse_width(char *ptr, t_fs *parsed_flags, va_list arglst)
{
	int res;
	int i;
	int width;

	i = 0;
	res = 0;
	if (ptr[i] == '*')
	{
		width = va_arg(arglst, unsigned int);
		if (width < 0)
		{
			width *= -1;
			parsed_flags->flag_minus = '-';
		}
		parsed_flags->width = width;
		i++;
	}
	while (ft_isdigit(ptr[i]))
	{
		res = 10 * res + (ptr[i] - '0');
		i++;
		parsed_flags->width = res;
	}
	return (i);
}

t_fs	*allocate_new_struct(t_fs *new)
{
	new = malloc(sizeof(t_fs));
	new->flag_minus = 0;
	new->flag_oct = 0;
	new->flag_plus = 0;
	new->flag_space = 0;
	new->flag_zero = 0;
	new->precision = -1;
	new->size = 0;
	new->type = 0;
	new->width = 0;
	new->argsign = 0;
	return (new);
}

int		parse_flags(char *format, t_fs *parsed_flags)
{
	int i;

	i = 0;
	while (is_flag(format[i]))
	{
		if (format[i] == '#')
			parsed_flags->flag_oct = format[i];
		if (format[i] == ' ')
			parsed_flags->flag_space = format[i];
		if (format[i] == '-')
			parsed_flags->flag_minus = format[i];
		if (format[i] == '+')
			parsed_flags->flag_plus = format[i];
		if (format[i] == '0')
			parsed_flags->flag_zero = format[i];
		i++;
	}
	return (i);
}

t_fs	*parse_format_string(char *format, va_list argslst)
{
	t_fs	*parsed_flags;
	int		i;

	i = 0;
	parsed_flags = NULL;
	parsed_flags = allocate_new_struct(parsed_flags);
	i += parse_flags(format, parsed_flags);
	while (!(is_type(format[i])))
	{
		if (ft_isdigit(format[i]) || format[i] == '*')
			i += parse_width(&format[i], parsed_flags, argslst);
		if (format[i] == '.' || format[i] == '*')
			i += parse_precision(&format[i + 1], parsed_flags, argslst);
		i += get_size(&format[i], parsed_flags);
		break ;
	}
	parsed_flags->type = format[i];
	parsed_flags->index = i + 2;
	return (parsed_flags);
}
