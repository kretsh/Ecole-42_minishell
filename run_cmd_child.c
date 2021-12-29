/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:15:20 by utygett           #+#    #+#             */
/*   Updated: 2021/12/23 12:17:38 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	run_cmd_child_part_two(t_data *data, t_cmd *cmd_start)
{
	if (cmd_start->flags.pipe_out == 0 && cmd_start->flags.pipe_in
		&& cmd_start->flags.redirect_left == 0
		&& cmd_start->flags.redirect_d_left == 0
		&& cmd_start->flags.redirect_right == 0
		&& cmd_start->flags.redirect_d_right == 0)
		run_cmd_child_in(data, cmd_start);
	else if (cmd_start->flags.redirect_right
		|| cmd_start->flags.redirect_d_right)
		run_cmd_child_red_right(data, cmd_start);
	else if (cmd_start->flags.redirect_left || cmd_start->flags.redirect_d_left)
		run_cmd_child_red_left(data, cmd_start);
	else
		run_cmd_child_else(data, cmd_start);
}

void	run_cmd_child_else(t_data *data, t_cmd *cmd_start)
{
	if (check_builtins(cmd_start, data) == NO)
	{
		execve(cmd_start->cmd, cmd_start->argv_for_cmd, data->envp);
		write(2, "execute error\n", 15);
		exit(126);
	}
	data->return_value /= 256;
	exit(data->return_value);
}

void	run_cmd_child(t_data *data, t_cmd *cmd_start)
{
	signal(SIGINT, SIG_DFL);
	if (envp_from_list_to_array(data))
		exit(EXIT_WITH_ERROR_1);
	if (cmd_start->flags.pipe_out && cmd_start->flags.pipe_in == 0
		&& cmd_start->flags.redirect_left == 0
		&& cmd_start->flags.redirect_d_left == 0
		&& cmd_start->flags.redirect_right == 0
		&& cmd_start->flags.redirect_d_right == 0)
		run_cmd_child_out(data, cmd_start);
	else if (cmd_start->flags.pipe_out && cmd_start->flags.pipe_in
		&& cmd_start->flags.redirect_left == 0
		&& cmd_start->flags.redirect_d_left == 0
		&& cmd_start->flags.redirect_right == 0
		&& cmd_start->flags.redirect_d_right == 0)
		run_cmd_child_in_out(data, cmd_start);
	else
		run_cmd_child_part_two(data, cmd_start);
}
