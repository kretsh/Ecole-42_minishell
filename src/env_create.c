/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 22:25:47 by cowen             #+#    #+#             */
/*   Updated: 2021/12/22 22:35:29 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	envp_from_list_to_array(t_data *data)
{
	int		i;
	int		j;
	int		k;
	t_cmd	*buf;

	if (!envp_init(data, &i, &buf))
		return (EXIT_WITH_ERROR_1);
	k = 0;
	while (buf)
	{
		i = ft_strlen(buf->cmd);
		j = ft_strlen(buf->value);
		if (j == 0)
		{
			buf = buf->next;
			continue ;
		}
		data->envp[k] = malloc(j + i + 1);
		if (check_malloc_for_envp(data, data->envp[k], k))
			return (EXIT_WITH_ERROR_1);
		env_concat_func(data, buf, j + i + 1, &k);
		buf = buf->next;
	}
	data->envp[k] = NULL;
	return (SUCCESS);
}

char	**path_parser_from_envp(t_cmd *start_envp)
{
	int		i;
	t_cmd	*buf;

	buf = start_envp;
	i = -1;
	while (buf)
	{
		if (ft_strncmp(buf->cmd, "PATH=", 5) == 0)
			break ;
		buf = buf->next;
	}
	if (!buf)
		return (NULL);
	return (ft_split(buf->value, ':'));
}
