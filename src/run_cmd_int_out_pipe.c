/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_int_out_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:06:40 by utygett           #+#    #+#             */
/*   Updated: 2021/12/23 12:10:18 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	run_cmd_child_out(t_data *data, t_cmd *cmd_start)
{
	close(cmd_start->pip[0]);
	dup2(cmd_start->pip[1], 1);
	if (check_builtins(cmd_start, data) == NO)
	{
		if (execve(cmd_start->cmd, cmd_start->argv_for_cmd, data->envp))
			write(2, "execute error\n", 15);
		exit(126);
	}
	data->return_value /= 256;
	exit(data->return_value);
}

void	run_cmd_child_in_out(t_data *data, t_cmd *cmd_start)
{
	dup2(cmd_start->prev->pip[0], 0);
	close(cmd_start->pip[0]);
	dup2(cmd_start->pip[1], 1);
	if (check_builtins(cmd_start, data) == NO)
	{
		if (execve(cmd_start->cmd, cmd_start->argv_for_cmd, data->envp))
			write(2, "execute error\n", 15);
		exit(126);
	}
	data->return_value /= 256;
	exit(data->return_value);
}

void	run_cmd_child_in(t_data *data, t_cmd *cmd_start)
{
	close(cmd_start->prev->pip[1]);
	dup2(cmd_start->prev->pip[0], 0);
	if (check_builtins(cmd_start, data) == NO)
	{
		if (execve(cmd_start->cmd, cmd_start->argv_for_cmd, data->envp))
			write(2, "execute error\n", 15);
		exit(126);
	}
	data->return_value /= 256;
	exit(data->return_value);
}
