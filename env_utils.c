/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 13:56:03 by utygett           #+#    #+#             */
/*   Updated: 2021/12/23 13:46:46 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	envp_init(t_data *data, int *i, t_cmd **buf)
{
	*buf = data->envp_list;
	*i = ft_lstsize(*buf);
	data->envp = malloc(sizeof(char *) * (*i + 1));
	if (data->envp == NULL)
		return (0);
	return (1);
}

void	env_concat_func(t_data *data, t_cmd *buf, int v, int *k)
{
	ft_strlcat(data->envp[*k], buf->cmd, v);
	ft_strlcat(data->envp[*k], buf->value, v);
	*k = *k + 1;
}

int	check_malloc_for_envp(t_data *data, char *envp, int k)
{
	if (envp == NULL)
	{
		while (--k >= 0)
			free(data->envp[k]);
		free(data->envp);
		return (1);
	}
	*data->envp[k] = '\0';
	return (0);
}

void	free_envp(t_data *data)
{
	int	i;

	i = 0;
	while (data->envp[i])
		free(data->envp[i++]);
	free(data->envp);
}
