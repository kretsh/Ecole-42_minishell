/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:58:48 by utygett           #+#    #+#             */
/*   Updated: 2021/12/23 14:28:31 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	make_envp(t_data *data, char **envp)
{
	int		i;
	int		equalsygn;
	t_cmd	*new;
	int		temp_value;

	i = -1;
	if (envp != NULL)
	{
		while (envp[++i])
		{
			if (ft_strnstr(envp[i], "SHLVL", 5))
			{
				temp_value = ft_atoi(&envp[i][6]) + 1;
				envp[i][6] = temp_value + '0';
			}
			equalsygn = ft_strchr(envp[i], '=') - envp[i] + 1;
			new = ft_lstnew(ft_substr(envp[i], 0, equalsygn), ft_substr(envp[i],
						 equalsygn, ft_strlen(envp[i]) - equalsygn));
			if (!new)
				return ;
			ft_lstadd_back(&data->envp_list, new);
		}
	}
	else
		data->envp_list = NULL;
}
