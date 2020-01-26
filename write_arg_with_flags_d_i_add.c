/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_arg_with_flags_d_i_add.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:48:19 by nmustach          #+#    #+#             */
/*   Updated: 2020/01/20 21:48:30 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		write_arg_(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		write(1, &arg[i], 1);
		i++;
	}
	return (i);
}

int		write_precision(int len)
{
	int ret;

	ret = 0;
	if (len > 0)
	{
		while (len--)
		{
			write(1, "0", 1);
			ret++;
		}
	}
	return (ret);
}

int		write_sign(char c)
{
	write(1, &c, 1);
	return (1);
}

int		write_space_flag(void)
{
	write(1, " ", 1);
	return (1);
}
