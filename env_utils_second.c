/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_second.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 17:51:28 by cowen             #+#    #+#             */
/*   Updated: 2021/12/23 13:04:11 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	print_env(t_cmd *list)
{
	if (list)
	{
		while (list)
		{
			if (ft_strchr(list->cmd, '='))
			{
				printf("%s", list->cmd);
				if (*(list->value) != 0)
					printf("%s", list->value);
				printf("\n");
				list = list->next;
			}
			else
				list = list->next;
		}
	}
}

char	*search_env(char *env, t_data *data)
{
	t_cmd	*list;
	size_t	envlen;

	if (check_in_search_env(data, &list, env, &envlen))
		return (ft_itoa(data->return_value));
	while (list)
	{
		if (*(list->cmd) != 0 && *(list->value) != 0)
		{
			if (ft_strncmp(env, list->cmd, envlen) == 0)
			{
				if (envlen == ft_strlen(list->cmd) - 1)
				{
					if (env)
						free(env);
					return (ft_strdup(list->value));
				}
			}
		}
		list = list->next;
	}
	if (env)
		free(env);
	return (NULL);
}

int	check_in_search_env(t_data *data, t_cmd **list, char *env, size_t *envlen)
{
	*envlen = ft_strlen(env);
	*list = data->envp_list;
	if (ft_strncmp(env, "?", 1) == 0)
	{
		free(env);
		return (1);
	}
	return (0);
}
