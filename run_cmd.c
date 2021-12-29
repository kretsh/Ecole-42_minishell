/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 21:56:52 by utygett           #+#    #+#             */
/*   Updated: 2021/12/23 12:17:39 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	run_cmd_pipe(t_data *data, t_cmd *cmd_start)
{
	if (cmd_start->flags.pipe_out)
	{
		if (pipe(cmd_start->pip) == -1)
		{
			write(2, "pipe error\n", 12);
			data->return_value = 1;
			return (PIPE_ERROR);
		}
	}
	return (EXIT_NO_ERROR);
}

int	run_cmd_builtins(t_data *data, t_cmd *cmd_start)
{
	if (cmd_start->flags.pipe_out == 0 && cmd_start->flags.pipe_in == 0
		&& cmd_start->flags.redirect_left == 0
		&& cmd_start->flags.redirect_d_left == 0
		&& cmd_start->flags.redirect_right == 0
		&& cmd_start->flags.redirect_d_right == 0)
	{
		if (check_builtins(cmd_start, data))
			return (YES);
	}
	return (NO);
}

void	run_cmd_waitpid(t_data *data, t_cmd *cmd_start)
{
	if (cmd_start->prev && cmd_start->prev->flags.pipe_in == 0
		&& cmd_start->prev->flags.pipe_out == 1)
		waitpid(cmd_start->prev->pid, &data->return_value, 0);
	if (cmd_start->flags.pipe_in == 1 && cmd_start->flags.pipe_out == 0)
		waitpid(cmd_start->pid, &data->return_value, 0);
	if (cmd_start->flags.pipe_in == 0 && cmd_start->flags.pipe_out == 0)
		waitpid(cmd_start->pid, &data->return_value, 0);
	if (cmd_start->flags.pipe_in == 1 && cmd_start->flags.pipe_out == 1)
		waitpid(cmd_start->pid, &data->return_value, 0);
}

int	run_cmd(t_data *data, t_cmd *cmd_start)
{
	if (run_cmd_pipe(data, cmd_start))
		return (EXIT_WITH_ERROR_1);
	if (!run_cmd_builtins(data, cmd_start))
		cmd_start->pid = fork();
	if (cmd_start->pid < 0)
		data->return_value = 1;
	signal(SIGINT, SIG_IGN);
	if (cmd_start->pid == CHILD)
		run_cmd_child(data, cmd_start);
	if (cmd_start->flags.pipe_in == 0 && cmd_start->flags.pipe_out == 1)
		close(cmd_start->pip[1]);
	if (cmd_start->flags.pipe_in == 1 && cmd_start->flags.pipe_out == 1)
	{
		close(cmd_start->prev->pip[0]);
		close(cmd_start->pip[1]);
	}
	if (cmd_start->flags.pipe_in == 1 && cmd_start->flags.pipe_out == 0)
		close(cmd_start->prev->pip[0]);
	run_cmd_waitpid(data, cmd_start);
	signal_catcher();
	data->return_value /= 256;
	return (EXIT_NO_ERROR);
}
