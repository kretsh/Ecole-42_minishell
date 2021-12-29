/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_third.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 17:18:14 by cowen             #+#    #+#             */
/*   Updated: 2021/12/22 22:33:57 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	check_parenthesis(t_cmd *lst, char *str)
{
	static int	parenthesis;

	if (lst->flags.start == 1)
		parenthesis = 0;
	if ((lst->prev && lst->prev->flags.quotes == NO) && lst->prev->c == '('
		&& (lst->prev->flags.d_quotes == NO) && ft_strchr(str, ')'))
		parenthesis_remove_flag(lst, &parenthesis, PREV);
	if ((lst->flags.quotes == NO)
		&& (lst->flags.d_quotes == NO) && lst->c == ')')
		parenthesis_remove_flag(lst, &parenthesis, CURR);
	lst->flags.parenthesis = parenthesis;
	if (((lst->flags.quotes == YES) || (lst->flags.d_quotes == YES))
		&& lst->c == ')')
	{
		while (lst->prev)
		{
			lst->flags.parenthesis = NO;
			if (lst->c == '(' && lst->flags.quotes == NO
				&& lst->flags.d_quotes == NO)
				lst->flags.remove = NO;
			lst = lst->prev;
		}
	}
}

void	parenthesis_remove_flag(t_cmd *lst, int *parenthesis, int flag)
{
	if (flag == PREV)
	{
		lst->prev->flags.remove = YES;
		*parenthesis = *parenthesis + 1;
	}
	if (flag == CURR)
	{
		if (!lst->prev || (lst->prev->c == '(' || *parenthesis == 0))
			lst->error_on_parsing = 1;
		lst->flags.remove = YES;
		*parenthesis = *parenthesis - 1;
	}
}

void	check_env(t_cmd *new_list)
{
	static int	env;

	if (new_list->flags.start == 1)
		env = 0;
	if (new_list->prev && new_list->flags.quotes == NO
		&& new_list->prev->c == '$')
		flag_remove(new_list, &env);
	if (env == YES && ft_strchr("|\'\"><& =/", new_list->c))
	{
		if (new_list->prev && new_list->prev->c == '$')
		{
			new_list->prev->flags.remove = 0;
			new_list->prev->flags.env = 0;
		}
		env = NO;
	}
	if (env == YES && (new_list->prev->c == '?'
			|| (ft_strchr("0123456789", new_list->prev->c)
				&& new_list->prev->prev->c == '$')))
		env = NO;
	if (env == YES)
	{
		new_list->flags.remove = YES;
		new_list->flags.env = env;
	}
}

void	check_tokens(t_cmd *new_list, char *str)
{
	if (new_list->prev == NO)
		new_list->flags.start = 1;
	new_list->flags.d_quotes = check_d_quotes(new_list, str);
	new_list->flags.quotes = check_quotes(new_list, str);
	new_list->flags.white_space = check_space(new_list);
	new_list->flags.cmd = check_cmd_num(new_list, str);
	check_argv(new_list);
	check_pipe(new_list, str);
	check_parenthesis(new_list, str);
	check_redirect_r(new_list);
	check_redirect_l(new_list);
	check_wild_card(new_list);
	check_env(new_list);
}

void	parse_quotes(t_data *data, char *str, t_cmd **start)
{
	t_cmd		*new_list;
	static int	parse_error;

	if (!str)
		return ;
	if (*start == NULL)
	{
		parse_error = 0;
		data->parse_error = 0;
	}
	if (!(*str))
	{
		data->parse_error = parse_error;
		return ;
	}
	new_list = ft_lstnew_char(*str);
	if (new_list == NULL)
		return ;
	ft_lstadd_back(start, new_list);
	check_tokens(new_list, str);
	if (new_list->error_on_parsing)
		parse_error = new_list->error_on_parsing;
	parse_quotes(data, str + 1, start);
}
