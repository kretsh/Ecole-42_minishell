/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:49:49 by utygett           #+#    #+#             */
/*   Updated: 2021/12/22 18:27:25 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	**list_to_str_arr(t_cmd **start)
{
	t_cmd	*buf;
	char	**arr;
	int		i;

	i = 0;
	buf = *start;
	while (buf)
	{
		printf("list = %s\n", buf->cmd);
		buf = buf->next;
		i++;
	}
	arr = malloc(sizeof(*arr) * (i + 1));
	if (arr == NULL)
		return (NULL);
	buf = *start;
	i = 0;
	while (buf)
	{
		arr[i++] = buf->cmd;
		buf = buf->next;
	}
	return (arr);
}

t_cmd	*ft_lstnew_char(char c)
{
	t_cmd	*new_list;

	new_list = malloc(sizeof(t_cmd));
	if (!new_list)
		return (NULL);
	new_list->pid = 1;
	new_list->c = c;
	new_list->flags = (t_flags){};
	new_list->error_on_parsing = 0;
	new_list->next = NULL;
	new_list->prev = NULL;
	new_list->cmd = NULL;
	new_list->value = NULL;
	new_list->argv_for_cmd = NULL;
	new_list->start_list = NULL;
	return (new_list);
}

int	check_d_quotes(t_cmd *new_list, char *str)
{
	static int	start_d_quotes;

	if (new_list->flags.start == 1)
		start_d_quotes = 0;
	if (new_list->c == '\"'
		&& (!new_list->prev || new_list->prev->flags.quotes == NO))
	{
		if (start_d_quotes == NO && ft_strchr(str + 1, '\"') != NO)
		{
			start_d_quotes = YES;
			new_list->flags.remove = YES;
		}
		else if (start_d_quotes == YES)
		{
			start_d_quotes = NO;
			new_list->flags.remove = YES;
		}
	}
	return (start_d_quotes);
}

int	check_quotes(t_cmd *new_list, char *str)
{
	static int	start_quotes;

	if (new_list->flags.start == 1)
		start_quotes = 0;
	if (new_list->c == '\'' && new_list->flags.d_quotes == NO)
	{
		if (start_quotes == NO && ft_strchr(str + 1, '\'') != NO)
		{
			start_quotes = YES;
			new_list->flags.remove = YES;
		}
		else if (start_quotes == YES)
		{
			new_list->flags.remove = YES;
			start_quotes = NO;
		}
	}
	return (start_quotes);
}

int	check_space(t_cmd *new_list)
{
	if (new_list->c == ' ')
	{
		if ((new_list->flags.quotes == YES)
			|| (new_list->flags.d_quotes == YES))
			new_list->flags.remove = NO;
		else
			new_list->flags.remove = YES;
		return (YES);
	}
	return (NO);
}
