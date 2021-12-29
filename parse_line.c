/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:29:22 by utygett           #+#    #+#             */
/*   Updated: 2021/12/23 12:58:07 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	parse_line_cmd_path(t_data *data, t_cmd *cmd_start)
{
	char	*path_cmd;

	path_cmd = search_cmd_paths(data, cmd_start->cmd);
	path_cmd = ft_strjoin(path_cmd, "/");
	data->path_to_cmd = ft_strjoin(path_cmd, cmd_start->cmd);
	free(cmd_start->cmd);
	cmd_start->cmd = NULL;
	free(path_cmd);
	cmd_start->cmd = data->path_to_cmd;
}

int	parse_line_cmd_dot_access(t_data *data, t_cmd *cmd_start)
{
	if (access(cmd_start->cmd, 0))
	{
		if (data->paths_to_binary)
			data->paths_to_binary = free_string_array(data->paths_to_binary);
		write(2, "command not found\n", 19);
		data->return_value = 127;
		return (EXIT_WITH_ERROR_1);
	}
	return (EXIT_NO_ERROR);
}

int	parse_line_cmd_dot(t_data *data, t_cmd *cmd_start)
{
	char	*path_cmd;

	path_cmd = get_pwd(GET_PATH_CURRENT_DIR, data);
	if (path_cmd == NULL)
	{
		if (data->paths_to_binary)
			data->paths_to_binary = free_string_array(data->paths_to_binary);
		return (EXIT_WITH_ERROR_1);
	}
	data->path_to_cmd = path_cmd;
	path_cmd = ft_strjoin(path_cmd, "/");
	if (data->path_to_cmd)
		free(data->path_to_cmd);
	data->path_to_cmd = ft_strjoin(path_cmd, cmd_start->cmd);
	if (path_cmd)
	{
		free(path_cmd);
		path_cmd = NULL;
	}
	cmd_start->cmd = data->path_to_cmd;
	if (parse_line_cmd_dot_access(data, cmd_start))
		return (EXIT_WITH_ERROR_1);
	free(path_cmd);
	return (EXIT_NO_ERROR);
}

int	parse_line(t_data *data, t_cmd *cmd_start)
{	
	if (cmd_start->cmd && cmd_start->cmd[0] != '.' && cmd_start->cmd[0] != '~'
		&& cmd_start->cmd[0] != '/' && !(check_builtins_here(cmd_start)))
		parse_line_cmd_path(data, cmd_start);
	else if (cmd_start->cmd && cmd_start->cmd[0] == '/'
		&& access(cmd_start->cmd, 0))
	{
		if (data->paths_to_binary)
			data->paths_to_binary = free_string_array(data->paths_to_binary);
		write(2, "No such file or directory\n", 27);
		data->return_value = 127;
		return (EXIT_WITH_ERROR_1);
	}
	else if (cmd_start->cmd && cmd_start->cmd[0] == '.')
	{
		if (parse_line_cmd_dot(data, cmd_start))
			return (EXIT_WITH_ERROR_1);
	}
	if (data->paths_to_binary)
		data->paths_to_binary = free_string_array(data->paths_to_binary);
	run_commands(data, cmd_start);
	return (EXIT_NO_ERROR);
}

int	run_commands(t_data *data, t_cmd *cmd_start)
{	
	if (!cmd_start->argv_for_cmd)
		exit(2);
	if (cmd_start->flags.or > 0 && data->return_value > 0)
		run_cmd(data, cmd_start);
	else if (cmd_start->flags.and > 0 && data->return_value == 0)
		run_cmd(data, cmd_start);
	else if (cmd_start->flags.and == NO && cmd_start->flags.or == NO)
		run_cmd(data, cmd_start);
	return (EXIT_NO_ERROR);
}
