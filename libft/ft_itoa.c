/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 20:19:22 by utygett           #+#    #+#             */
/*   Updated: 2021/10/08 12:44:24 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	str_reverse(char *str)
{	
	int		i;
	char	b;

	i = 0;
	if (*str == '-')
		str++;
	while ((int)ft_strlen(str) / 2 > i)
	{
		b = *(str + i);
		*(str + i) = *(str + ((int)ft_strlen(str) - i - 1));
		*(str + ((int)ft_strlen(str) - i - 1)) = b;
		i++;
	}
}

char	*ft_itoa(int n)
{
	char	str[12];
	int		i;

	i = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
		i++;
	}
	while (n || (i == 0 && n == 0))
	{	
		str[i] = (n % 10) + '0';
		n = n / 10;
		i++;
	}
	str[i] = '\0';
	str_reverse(str);
	return (ft_strdup(str));
}
