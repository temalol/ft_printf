/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dec_to_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmustach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:45:57 by nmustach          #+#    #+#             */
/*   Updated: 2020/01/20 21:13:48 by nmustach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*return_zero(char *arr)
{
	arr[0] = '0';
	arr[1] = '\0';
	return (arr);
}

char	*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = ft_strlen(str);
	j--;
	while (i < j)
	{
		tmp = str[j];
		str[j] = str[i];
		str[i] = tmp;
		j--;
		i++;
	}
	return (str);
}

char	*dec_to_base(size_t n, int base, char up)
{
	char	*arr;
	int		tmp;
	int		i;

	i = 0;
	arr = malloc(sizeof(char) * 65);
	if (n == 0)
		return (return_zero(arr));
	while (n != 0)
	{
		tmp = 0;
		tmp = n % base;
		if (tmp < 10)
			arr[i++] = tmp + '0';
		else
		{
			arr[i] = tmp + 'W';
			if (up == 'X')
				arr[i] = ft_toupper(arr[i]);
			i++;
		}
		n = n / base;
	}
	arr[i] = '\0';
	return (ft_strrev(arr));
}

char	*dec_to_base_unsigned_long(unsigned long n, int base, char up)
{
	char	*arr;
	int		tmp;
	int		i;

	i = 0;
	arr = malloc(sizeof(char) * 21);
	if (n == 0)
		return (return_zero(arr));
	while (n != 0)
	{
		tmp = 0;
		tmp = n % base;
		if (tmp < 10)
			arr[i++] = tmp + '0';
		else
		{
			arr[i] = tmp + 'W';
			if (up == 'X')
				arr[i] = ft_toupper(arr[i]);
			i++;
		}
		n = n / base;
	}
	arr[i] = '\0';
	return (ft_strrev(arr));
}
