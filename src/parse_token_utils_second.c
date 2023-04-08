/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_utils_second.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:29:58 by cowen             #+#    #+#             */
/*   Updated: 2021/12/22 22:34:37 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	pipe_checking(t_cmd *list, char *str, int *cmd)
{
	flag_initilization(list, 2, NO, NO);
	check_next_symbol(str, cmd);
}

void	null_pipes(int *pipe_in, int *pipe_out)
{
	*pipe_in = 0;
	*pipe_out = 0;
}

void	flag_remove(t_cmd *new_list, int *env)
{
	new_list->prev->flags.remove = 1;
	new_list->prev->flags.env = 0;
	*env = YES;
}
