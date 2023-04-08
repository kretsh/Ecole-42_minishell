/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 20:05:30 by utygett           #+#    #+#             */
/*   Updated: 2021/12/23 18:34:25 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	write_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, str + i, 1);
		i++;
	}
}

int	check_flags_n(char *argv)
{
	int	i;
	int	n;
	int	e;

	i = 1;
	e = 0;
	n = 0;
	if (argv[0] == '-')
	{
		while (argv[i])
		{
			if (argv[i] == '-' && (argv[i] != 'n' || argv[i] != 'e'))
				return (0);
			if (argv[i] == 'n')
				n = 1;
			if (argv[i] == 'e')
				e = 2;
			i++;
		}
	}
	else
		return (0);
	return (n + e);
}

int	my_echo(char **argv)
{
	int	i;
	int	endl;
	int	usage;

	endl = 0;
	i = 1;
	while (argv[i])
	{
		usage = check_flags_n(argv[i]);
		if (usage == 0)
			break ;
		else if (usage == 1 || usage == 3 || usage == 5 || usage == 7)
			endl = 1;
		i++;
	}
	while (argv[i])
	{		
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (endl != 1)
		write(1, "\n", 1);
	return (0);
}

int	my_cd(char **argv, t_cmd *envp_list)
{	
	int		error;
	char	*path;

	if (!argv[1])
	{
		path = home_dir(envp_list);
		if (path)
			chdir(path);
		else
			return (256);
	}
	else
	{
		error = chdir(argv[1]);
		if (error != 0)
		{
			write(2, "cd:  No such file or directory\n", 32);
			return (256);
		}
	}
	return (SUCCESS);
}

char	*home_dir(t_cmd *envp_list)
{
	int	i;

	i = -1;
	while (envp_list)
	{
		if (ft_strncmp(envp_list->cmd, "HOME=", 5) == 0)
			break ;
		envp_list = envp_list->next;
	}
	if (!envp_list)
	{
		write(2, "cd: HOME not set\n", 18);
		return (NULL);
	}
	return (envp_list->value);
}
