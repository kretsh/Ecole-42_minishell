/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 16:55:47 by utygett           #+#    #+#             */
/*   Updated: 2021/10/09 14:32:28 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (*(dst + i) && i < dstsize)
		i++;
	len = i;
	while (*(src + i - len) && i + 1 < dstsize)
	{
		*(dst + i) = *(src + i - len);
		i++;
	}
	if (len < dstsize)
		*(dst + i) = '\0';
	return (len + ft_strlen(src));
}
