/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_second.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 14:55:38 by cowen             #+#    #+#             */
/*   Updated: 2021/12/22 22:34:25 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	check_cmd_num(t_cmd *list, char *str)
{
	static int	cmd;
	static int	and;
	static int	or;

	error_on_parsing_flag(list, str);
	null_static_values(list, &cmd, &or, &and);
	if ((list->flags.quotes == 0)
		&& (list->flags.d_quotes == 0) && ft_strchr("|&", list->c))
	{
		if (list->prev && list->prev->c == '|' && list->c == '|')
		{
			flag_initilization(list, 1, NO, NO);
			and_oder_or_checking(1, &and, &or);
		}
		else if (list->prev && list->prev->c != '|' && list->c == '|')
			pipe_checking(list, str, &cmd);
		if (list->prev && list->prev->c == '&' && list->c == '&')
		{
			check_next_symbol(str, &cmd);
			and_oder_or_checking(2, &and, &or);
			flag_initilization(list, 3, NO, NO);
		}
	}
	flag_initilization(list, 4, or, and);
	return (cmd);
}

void	check_argv(t_cmd *new_list)
{
	static int	cmd;

	if (new_list->flags.start == 1)
		cmd = 0;
	if (new_list->prev)
		new_list->flags.argv = new_list->prev->flags.argv;
	if (cmd != new_list->flags.cmd)
	{
		cmd = new_list->flags.cmd;
		new_list->flags.argv = 0;
	}
	if ((new_list->flags.quotes == NO)
		&& (new_list->flags.d_quotes == NO) && new_list->c == ' ')
	{
		if (new_list->prev && new_list->prev->c != ' ')
			new_list->flags.argv++;
	}
}

int	check_pipe_parse_error(t_cmd *new_list, char *str)
{
	if (!new_list->prev)
		return (1);
	if (new_list->prev && ft_strchr("&><", new_list->prev->c))
		return (1);
	if (new_list->prev && ft_strchr("&><\0", *(str + 1)))
		return (1);
	if (*(str + 1) == '\0')
		return (1);
	return (0);
}

void	check_pipe(t_cmd *lst, char *str)
{
	static int	pipe_in;	
	static int	pipe_out;

	if (lst->c == '|')
		lst->error_on_parsing = check_pipe_parse_error(lst, str);
	if (lst->flags.start == 1)
		null_pipes(&pipe_in, &pipe_out);
	if (lst->prev && (lst->flags.quotes == NO) && (lst->flags.d_quotes == NO)
		&& ft_strchr(str, '|') && *(ft_strchr(str, '|') + 1) != '|'
		&& *(ft_strchr(str, '|') - 1) != '|')
	{
		if (pipe_in == NO && lst->c == '|')
			pipe_in = YES;
		if (lst->prev && lst->prev->flags.quotes == NO
			&& lst->prev->flags.d_quotes == NO && lst->c == '|')
			lst->prev->flags.pipe_out = YES;
	}
	else
		null_pipes(&pipe_in, &pipe_out);
	lst->flags.pipe_in = pipe_in;
	lst->flags.pipe_out = pipe_out;
}

void	check_wild_card(t_cmd *list)
{
	static int	wild_card;	
	t_cmd		*buf;

	buf = list;
	if (list->flags.start == 1)
		wild_card = 0;
	if (list->prev && list->prev->c == ' ' && (list->flags.quotes == NO)
		&& (list->flags.d_quotes == NO) && list->c == '*')
		wild_card = YES;
	else if (list->prev && list->prev->c == ' ' && (list->flags.quotes == NO)
		&& (list->flags.d_quotes == NO) && list->c == '~')
		wild_card = 2;
	else
		wild_card = NO;
	list->flags.wild_card = wild_card;
}
