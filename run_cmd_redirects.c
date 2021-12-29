/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_redirects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:11:35 by utygett           #+#    #+#             */
/*   Updated: 2021/12/23 12:13:34 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	run_cmd_child_red_right_part_two(t_data *data,
			t_cmd *cmd_start, int temppoint)
{
	if (temppoint)
	{
		dup2(temppoint, 1);
		if (cmd_start->flags.pipe_out == 1)
		{
			close(cmd_start->prev->pip[1]);
			close(cmd_start->prev->pip[0]);
		}
		else if (cmd_start->flags.pipe_in == 1)
		{
			close(cmd_start->prev->pip[1]);
			close(cmd_start->prev->pip[0]);
		}
		if (check_builtins(cmd_start, data) == NO)
		{		
			if (execve(cmd_start->cmd, cmd_start->argv_for_cmd, data->envp))
				write(2, "execute error\n", 15);
			exit(126);
		}
		close(temppoint);
		data->return_value /= 256;
		exit(data->return_value);
	}
}

void	run_cmd_child_red_right(t_data *data, t_cmd *cmd_start)
{
	int			temppoint;

	temppoint = 0;
	if (cmd_start->flags.redirect_d_right)
		temppoint = open(cmd_start->flags.redirect_filename, O_CREAT | O_RDWR
				| O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		temppoint = open(cmd_start->flags.redirect_filename, O_CREAT | O_RDWR
				| O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (temppoint < 0)
		exit(1);
	run_cmd_child_red_right_part_two(data, cmd_start, temppoint);
}

void	run_cmd_child_red_left_part_three(t_data *data,
		t_cmd *cmd_start, int temppoint)
{
	if (cmd_start->cmd && check_builtins(cmd_start, data) == NO)
	{	
		execve(cmd_start->cmd, cmd_start->argv_for_cmd, data->envp);
		write(2, "execute error\n", 15);
		exit(126);
	}
	close(temppoint);
	data->return_value /= 256;
	exit(data->return_value);
}

void	run_cmd_child_red_left_part_two(t_data *data,
		t_cmd *cmd_start, int temppoint)
{
	temppoint = open(cmd_start->flags.redirect_filename, O_RDONLY);
	if (temppoint < 0)
	{
		write(2, "No such file or directory\n", 27);
		exit(1);
	}
	if (cmd_start->flags.redirect_d_left)
		unlink("heredoc.tmp");
	if (cmd_start->flags.pipe_out == 1)
	{
		close(cmd_start->pip[0]);
		dup2(cmd_start->pip[1], 1);
	}
	else if (cmd_start->flags.pipe_in == 1
		&& cmd_start->flags.redirect_d_left == 1)
	{
		close(cmd_start->prev->pip[1]);
		close(cmd_start->prev->pip[0]);
	}
	dup2(temppoint, 0);
	run_cmd_child_red_left_part_three(data, cmd_start, temppoint);
}

void	run_cmd_child_red_left(t_data *data, t_cmd *cmd_start)
{
	int			temppoint;
	char		*line;

	temppoint = 0;
	if (cmd_start->flags.redirect_d_left)
	{
		rl_clear_history();
		temppoint = open("heredoc.tmp", O_CREAT | O_RDWR | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			line = readline(">");
			if (!line || !ft_strcmp(line, cmd_start->flags.redirect_filename))
				break ;
			write(temppoint, line, ft_strlen(line));
			free(line);
			write(temppoint, "\n", 1);
		}
		free(cmd_start->flags.redirect_filename);
		cmd_start->flags.redirect_filename = ft_strdup("heredoc.tmp");
		close(temppoint);
	}
	run_cmd_child_red_left_part_two(data, cmd_start, temppoint);
}
