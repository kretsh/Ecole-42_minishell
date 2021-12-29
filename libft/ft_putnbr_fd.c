/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:55:27 by utygett           #+#    #+#             */
/*   Updated: 2021/10/08 14:23:38 by utygett          ###   ########.fr       */
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

void	ft_putnbr_fd(int n, int fd)
{
	char	str[12];
	int		i;

	i = 0;
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			n = -n;
		}
		while (n || (i == 0 && n == 0))
		{	
			str[i] = (n % 10) + '0';
			n = n / 10;
			i++;
		}
		str[i] = '\0';
		str_reverse(str);
		ft_putstr_fd(str, fd);
	}
}
