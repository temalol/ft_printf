/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_flag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:31:16 by nmustach          #+#    #+#             */
/*   Updated: 2020/01/20 18:52:11 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_double_size(char *format, t_fs *parsed_flags)
{
	int i;

	i = 0;
	if (format[i] == 'h' && format[i + 1] == 'h')
	{
		parsed_flags->size = HH;
		return (2);
	}
	if (format[i] == 'l' && format[i + 1] == 'l')
	{
		parsed_flags->size = LL;
		return (2);
	}
	return (0);
}

int	get_size(char *format, t_fs *parsed_flags)
{
	int i;

	i = 0;
	if ((format[i] == 'h' && format[i + 1] == 'h') ||
	(format[i] == 'l' && format[i + 1] == 'l'))
		return (get_double_size(format, parsed_flags));
	if (format[i] == 'h')
	{
		parsed_flags->size = H;
		return (1);
	}
	if (format[i] == 'l')
	{
		parsed_flags->size = L;
		return (1);
	}
	if (format[i] == 'L')
	{
		parsed_flags->size = LF;
		return (1);
	}
	return (0);
}

int	is_type(char type)
{
	if (ft_strchr(TYPE, type) && type)
		return (1);
	return (0);
}

int	is_flag(char flag)
{
	if (ft_strchr(FLAG, flag))
		return (1);
	return (0);
}
