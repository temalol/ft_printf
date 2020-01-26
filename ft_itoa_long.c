/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 15:34:34 by nmustach          #+#    #+#             */
/*   Updated: 2020/01/20 20:29:56 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*fillarray(char *str, int len, long n)
{
	int flag;
	int	b;

	if (n < 0)
	{
		n = n * (-1);
		flag = 1;
	}
	while (n > 0)
	{
		b = n % 10;
		str[--len] = b + '0';
		n = n / 10;
	}
	if (flag == 1)
		str[0] = '-';
	return (str);
}

static	int	count_numbers(long n)
{
	int	cnt;

	cnt = 0;
	if (n < 0)
	{
		cnt++;
		n = n * (-1);
	}
	while (n >= 10)
	{
		n = n / 10;
		cnt++;
	}
	return (cnt + 1);
}

char		*ft_itoa_long(long n)
{
	char	*str;
	int		len;

	if ((unsigned long)n == -9223372036854775808U)
		return (ft_strdup("-9223372036854775808"));
	if (n == 0)
		return (ft_strdup("0"));
	len = count_numbers(n);
	str = (char*)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	return (fillarray(str, len, n));
}
