/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 17:28:23 by utygett           #+#    #+#             */
/*   Updated: 2021/12/22 23:34:22 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	**free_string_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	return (NULL);
}

void	free_line(t_cmd *line)
{
	t_cmd	*buf1;
	t_cmd	*buf2;

	buf1 = line;
	while (buf1)
	{
		buf2 = buf1;
		buf1 = buf1->next;
		free(buf2);
		buf2 = NULL;
	}
}

void	free_envp_list(t_cmd *envp_list)
{
	t_cmd	*buf;

	while (envp_list)
	{
		buf = envp_list;
		envp_list = envp_list->next;
		if (buf->cmd)
			free(buf->cmd);
		if (buf->value)
			free(buf->value);
		free(buf);
	}
}

void	free_cmd(t_data *data)
{
	t_cmd	*buf;
	t_cmd	*buf1;

	if (data->paths_to_binary)
		data->paths_to_binary = free_string_array(data->paths_to_binary);
	buf = data->cmd_start;
	if (data->line_from_read)
		free(data->line_from_read);
	if (buf)
	{
		while (buf)
		{
			if (buf->cmd)
				free(buf->cmd);
			if (buf->flags.redirect_filename)
				free_redirect(buf);
			if (buf->argv_for_cmd)
				buf->argv_for_cmd = free_string_array(buf->argv_for_cmd);
			buf1 = buf;
			buf = buf->next;
			free(buf1);
		}
	}
}

void	free_redirect(t_cmd *buf)
{
	free(buf->flags.redirect_filename);
	buf->flags.redirect_filename = NULL;
}
