/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_and_argv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 11:12:35 by utygett           #+#    #+#             */
/*   Updated: 2021/12/23 16:05:56 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*char_add_to_str(char *str, char c)
{
	char	*buf;
	int		len;

	if (!str)
	{
		str = now_str_before(str, c);
		return (str);
	}
	len = ft_strlen(str);
	buf = malloc(sizeof(char) * (len + 2));
	if (!buf)
		return (NULL);
	len = 0;
	while (str[len])
	{
		buf[len] = str[len];
		len++;
	}
	buf[len++] = c;
	buf[len] = '\0';
	free(str);
	return (buf);
}

char	*get_argv(char *str, t_cmd *line, t_data *data, char **redir_filename)
{
	static char	*env;
	char		*buf_str;

	if (line && line->flags.env == 1)
		env = char_add_to_str(env, line->c);
	if (env && (!line->next || line->next->flags.env == 0))
	{
		env = search_env(env, data);
		if (env)
		{
			buf_str = get_argv_if_env_exist(str, env);
			env = NULL;
			return (buf_str);
		}
	}
	if (line && line->flags.remove == 0 && (line->flags.redirect_right == YES
			|| line->flags.redirect_d_right == YES
			|| line->flags.redirect_left == YES
			|| line->flags.redirect_d_left == YES))
		*redir_filename = char_add_to_str(*redir_filename, line->c);
	else if (line && line->flags.remove == 0)
		str = char_add_to_str(str, line->c);
	return (str);
}

void	get_cmd_and_argv_from_list_two(t_data *data, t_cmd *list)
{
	int		i;
	t_cmd	*buf;
	t_cmd	*buf1;
	t_cmd	*buf2;

	buf1 = list;
	buf = buf1->start_list;
	i = ft_lstsize(buf);
	buf1->argv_for_cmd = malloc(sizeof(char *) * (i + 1));
	if (!buf1->argv_for_cmd)
		return ;
	buf = buf1->start_list;
	i = 0;
	while (buf)
	{
		buf1->argv_for_cmd[i++] = buf->value;
		buf2 = buf;
		buf = buf->next;
		free(buf2);
	}
	buf1->argv_for_cmd[i] = NULL;
	if (buf1->flags.parenthesis == YES)
		buf1->cmd = search_env(ft_strdup("_"), data);
	else
		buf1->cmd = ft_strdup(buf1->argv_for_cmd[0]);
}

void	get_cmd(t_cmd *ln, t_cmd **command_list, t_data *data)
{
	static int	cmd;
	int			argv;
	char		*str;
	t_cmd		*new_list;

	if (parsing_init(ln, &cmd, &new_list, &argv))
		return ;
	while (ln && cmd == ln->flags.cmd)
	{
		str = NULL;
		while (ln && argv == ln->flags.argv && cmd == ln->flags.cmd)
		{
			str = get_cmd_if_argv_doesnt_exist(str, ln, new_list);
			parenthesis_parsing(&ln, &str, &cmd);
			if (!ln)
				break ;
			str_init_in_parsing(&ln, &str, data, new_list);
		}
		checking_after_parsing(new_list, ln, str, &argv);
	}
	cmd_init_in_parsing(ln, &cmd);
	if (get_cmd_parse_and_error(new_list, command_list, data))
		return ;
	parse_line(data, new_list);
	get_cmd(ln, command_list, data);
}

int	get_cmd_parse_and_error(t_cmd *new_list, t_cmd **command_list, t_data *data)
{
	ft_lstadd_back(command_list, new_list);
	get_cmd_and_argv_from_list_two(data, new_list);
	data->paths_to_binary = path_parser_from_envp(data->envp_list);
	if (data->parse_error != 0)
	{
		write(2, "parse error\n", 12);
		data->return_value = 2;
		return (1);
	}
	return (0);
}
