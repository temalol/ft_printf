/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsigned_long.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 19:59:16 by nmustach          #+#    #+#             */
/*   Updated: 2020/01/20 20:30:52 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*fillarray(char *str, int len, unsigned long n)
{
	int	b;

	while (n > 0)
	{
		b = n % 10;
		str[--len] = b + '0';
		n = n / 10;
	}
	return (str);
}

static	int	count_numbers(unsigned long n)
{
	int	cnt;

	cnt = 0;
	while (n >= 10)
	{
		n = n / 10;
		cnt++;
	}
	return (cnt + 1);
}

char		*ft_itoa_unsigned_long(unsigned long n)
{
	char	*str;
	int		len;

	if (n == 0)
		return (ft_strdup("0"));
	len = count_numbers(n);
	str = (char*)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	return (fillarray(str, len, n));
}
