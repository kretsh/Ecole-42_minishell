/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bultins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:25:27 by utygett           #+#    #+#             */
/*   Updated: 2021/12/23 12:26:10 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	check_builtins_firt_part(t_cmd *cmd_start, t_data *data)
{
	if (ft_strncmp(cmd_start->argv_for_cmd[0], "exit", 5) == 0)
	{
		exit_with_exit(data, cmd_start->argv_for_cmd);
		return (YES);
	}
	else if ((ft_strncmp(cmd_start->argv_for_cmd[0], "echo", 5) == 0))
	{
		data->return_value = my_echo(cmd_start->argv_for_cmd);
		return (YES);
	}
	else if (ft_strncmp(cmd_start->argv_for_cmd[0], "cd", 3) == 0)
	{
		data->return_value = my_cd(cmd_start->argv_for_cmd, data->envp_list);
		return (YES);
	}
	else if (ft_strncmp(cmd_start->argv_for_cmd[0], "env", 4) == 0)
	{
		print_env(data->envp_list);
		return (YES);
	}
	return (NO);
}

int	check_builtins(t_cmd *cmd_start, t_data *data)
{	
	if (check_builtins_firt_part(cmd_start, data))
		return (YES);
	if (ft_strncmp(cmd_start->argv_for_cmd[0], "pwd", 4) == 0)
	{
		get_pwd(WRITE_PATH_CURRENT_DIR, data);
		return (YES);
	}
	else if (ft_strncmp(cmd_start->argv_for_cmd[0], "unset", 6) == 0)
	{
		del_from_env(cmd_start->argv_for_cmd, data->envp_list, data);
		return (YES);
	}
	else if (ft_strncmp(cmd_start->argv_for_cmd[0], "export", 7) == 0)
	{
		export_to_env(cmd_start->argv_for_cmd, &data->envp_list, data);
		return (YES);
	}
	else if (!cmd_start->cmd)
	{
		write(2, "command not found\n", 18);
		data->return_value = 127 * 256;
		return (YES);
	}
	return (NO);
}

int	check_builtins_here(t_cmd *cmd_start)
{	
	if (ft_strncmp(cmd_start->argv_for_cmd[0], "exit", 5) == 0)
		return (YES);
	else if (ft_strncmp(cmd_start->argv_for_cmd[0], "echo", 5) == 0)
		return (YES);
	else if (ft_strncmp(cmd_start->argv_for_cmd[0], "cd", 3) == 0)
		return (YES);
	else if (ft_strncmp(cmd_start->argv_for_cmd[0], "env", 4) == 0)
		return (YES);
	else if (ft_strncmp(cmd_start->argv_for_cmd[0], "pwd", 4) == 0)
		return (YES);
	else if (ft_strncmp(cmd_start->argv_for_cmd[0], "unset", 6) == 0)
		return (YES);
	else if (ft_strncmp(cmd_start->argv_for_cmd[0], "export", 7) == 0)
		return (YES);
	return (NO);
}
