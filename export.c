/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 19:28:15 by cowen             #+#    #+#             */
/*   Updated: 2021/12/23 16:50:29 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	check_valid_export(char *argv, int flag)
{
	int	i;

	i = 1;
	if (ft_isalpha(argv[0]) || argv[0] == '_')
	{
		while (argv[i])
		{
			if (!(ft_isalnum(argv[i])) && argv[i] != '_')
			{
				if (argv[i] == '=' && flag == 1)
					return (1);
				if (argv[i] != '=')
					return (1);
				else
					return (0);
			}
			i++;
		}
	}
	else
		return (1);
	return (0);
}

void	export_to_env(char **argv, t_cmd **list, t_data *data)
{
	t_cmd	*temp;
	int		i;
	int		flag;

	flag = 0;
	i = 1;
	temp = *list;
	if (!argv[i])
		export_no_arguments(list);
	else
	{
		while (argv[i])
		{
			if (export_with_arguments(argv[i], list, data))
				flag = 1;
			i++;
		}
	}
	if (flag == 0)
		data->return_value = 0;
}

int	export_with_arguments(char *argv, t_cmd **ls, t_data *data)
{
	t_cmd	*temp;
	int		flag;
	int		equalsign;

	temp = *ls;
	flag = 0;
	if (check_valid_export(argv, 0))
		flag = write_export_error(data, argv);
	else
	{
		if (!check_argv_for_existing(argv, ls))
		{
			if (!ft_strchr(argv, '='))
				ft_lstadd_back(ls, ft_lstnew(ft_strdup(argv), ft_calloc(1, 1)));
			else
			{
				equalsign = ft_strchr(argv, '=') - argv + 1;
				temp = ft_lstnew(ft_substr(argv, 0, equalsign),
						ft_substr(argv, equalsign,
							ft_strlen(argv) - equalsign));
				ft_lstadd_back(ls, temp);
			}
		}
	}
	return (flag);
}

int	check_argv_for_existing(char *argv, t_cmd **list)
{
	t_cmd	*temp;
	int		equalsign;

	temp = *list;
	if (!ft_strchr(argv, '='))
		return (check_argv_for_existing_without_equal(argv, list));
	else
	{
		equalsign = ft_strchr(argv, '=') - argv + 1;
		while (temp)
		{
			if (!ft_strncmp(argv, temp->cmd, equalsign - 1))
			{
				free(temp->value);
				free(temp->cmd);
				temp->cmd = ft_substr(argv, 0, equalsign);
				temp->value = ft_substr(argv, equalsign,
						ft_strlen(argv) - equalsign);
				return (YES);
			}
			temp = temp->next;
		}
	}
	return (NO);
}

void	del_from_env(char **argv, t_cmd *list, t_data *data)
{
	t_cmd	*temp;
	t_cmd	*temp2;

	temp = list;
	if (temp)
	{
		while (temp->next)
		{
			if (check_valid_export(argv[1], 1))
			{
				write_unset(data, argv[1]);
				break ;
			}
			else
			{
				if (!(ft_strncmp(argv[1], temp->next->cmd,
							ft_strlen(temp->next->cmd) - 1)))
				{	
					new_chain(temp, &temp2);
					return ;
				}
				temp = temp->next;
			}
		}
	}
}
