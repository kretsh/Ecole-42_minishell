/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:53:01 by cowen             #+#    #+#             */
/*   Updated: 2021/12/22 22:32:46 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	and_oder_or_checking(int flag, int *and, int *or)
{
	if (flag == 1)
	{
		*and = 0;
		*or = *or + 1;
	}
	else if (flag == 2)
	{
		*or = 0;
		*and = *and + 1;
	}
}

void	check_next_symbol(char *str, int *cmd)
{
	if (*(str + 1))
		*cmd = *cmd + 1;
}

void	null_static_values(t_cmd *list, int *cmd, int *or, int *and)
{
	if (list->flags.start == 1)
	{
		*cmd = 0;
		*or = 0;
		*and = 0;
	}
}

void	flag_initilization(t_cmd *list, int flag, int or, int and)
{
	if (flag == 1)
	{
		list->prev->flags.or = YES;
		list->prev->flags.and = NO;
		list->flags.remove = YES;
	}
	else if (flag == 2)
		list->flags.remove = YES;
	else if (flag == 3)
	{
		list->flags.remove = YES;
		list->prev->flags.remove = YES;
	}
	else if (flag == 4)
	{
		list->flags.or = or;
		list->flags.and = and;
	}
}

void	error_on_parsing_flag(t_cmd *list, char *str)
{
	if (ft_strchr("|&><", list->c) && *(str + 1) == '\0')
		list->error_on_parsing = 1;
}
