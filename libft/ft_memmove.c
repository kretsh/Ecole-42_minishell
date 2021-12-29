/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:51:23 by utygett           #+#    #+#             */
/*   Updated: 2021/10/05 15:33:21 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	while (len > 0)
	{	
		if ((src - dst) >= 0)
		{
			*((char *)dst + i) = *((char *)src + i);
			i++;
		}
		else
		{
			*((char *)dst + len - 1) = *((char *)src + len - 1);
		}
		len--;
	}
	return (dst);
}
