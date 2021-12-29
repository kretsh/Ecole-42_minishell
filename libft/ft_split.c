/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 10:39:14 by utygett           #+#    #+#             */
/*   Updated: 2021/10/08 22:50:38 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*word_to_str(char *s, char c, int *error_mem);
static char	*skip_word(char *s, char c);
static char	**free_mem(char **str1, int size);
static char	**malloc_array(int *sepnb, char *s, char c);

char	**ft_split(char const *s, char c)
{
	char	**str1;
	int		sepnb;
	int		i;
	int		error_mem;

	if (!s)
		return (NULL);
	while (*s == c && c != '\0' && *s)
		s++;
	error_mem = 0;
	str1 = malloc_array(&sepnb, (char *)s, c);
	if (!str1)
		return (NULL);
	i = 0;
	while (sepnb > i && error_mem == 0)
	{
		*(str1 + i) = (char *)word_to_str((char *)s, c, &error_mem);
		s = skip_word((char *)s, c);
		i++;
	}
	if (error_mem)
		return (free_mem(str1, i - 1));
	*(str1 + i) = NULL;
	return (str1);
}

static char	**malloc_array(int *sepnb, char *s, char c)
{	
	char	**str1;
	int		i;

	i = 0;
	*sepnb = 0;
	while (*(s + i))
	{
		if (*(s + i) != c && (i == 0 || *(s + i - 1) == c))
			(*sepnb)++;
		i++;
	}
	str1 = malloc(sizeof(*str1) * (*sepnb + 1));
	if (!str1)
		return (NULL);
	return (str1);
}

static char	**free_mem(char **str1, int size)
{
	while (size > 0)
	{
		free(str1[size - 1]);
		size--;
	}
	free(str1);
	return (NULL);
}

static char	*word_to_str(char *s, char c, int *error_mem)
{
	char	*word;
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (*(s + size) != c && *(s + size))
		size++;
	word = malloc(sizeof(*word) * (size + 1));
	if (word == 0)
	{
		*error_mem = 1;
		return (NULL);
	}
	while (size > i)
	{
		*(word + i) = *(s + i);
		i++;
	}
	*(word + i) = '\0';
	return (word);
}

static char	*skip_word(char *s, char c)
{	
	while (*s != c && *s)
		s++;
	while (*s == c && *s)
		s++;
	return (s);
}
