/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:15:55 by utygett           #+#    #+#             */
/*   Updated: 2021/12/23 13:09:56 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	if (!(*s1))
		return (ft_calloc(1, 1));
	p = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!p)
		return (NULL);
	while (*s1)
	{
		*(p + i) = *s1;
		s1++;
		i++;
	}
	*(p + i) = '\0';
	return (p);
}
