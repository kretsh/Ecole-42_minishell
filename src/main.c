/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:58:56 by cowen             #+#    #+#             */
/*   Updated: 2021/12/23 18:46:32 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	parse_cmd_argv(t_data *data)
{
	t_cmd	*line;

	line = NULL;
	data->cmd_start = NULL;
	parse_quotes(data, data->line_from_read, &line);
	get_cmd_and_argv_from_line(data, &line);
	free_line(line);
}

char	*get_pwd(int flag, t_data *data)
{
	char	path_currend_dir[PATH_MAX];

	if (getcwd(path_currend_dir, PATH_MAX) == NULL)
	{
		data->return_value = 1;
		write(2, "error getcwd\n", 14);
		return (NULL);
	}
	if (flag == GET_PATH_CURRENT_DIR)
		return (ft_strdup(path_currend_dir));
	if (flag == WRITE_PATH_CURRENT_DIR)
	{
		printf("%s\n", path_currend_dir);
		data->return_value = 0;
		return (NULL);
	}
	return (NULL);
}

void	sub_minishell(t_data *data, char **argv)
{
	data->line_from_read = ft_strtrim(argv[0], " 	");
	if (!data->line_from_read)
		exit(1);
	parse_cmd_argv(data);
	exit(data->return_value);
}

void	start_parse(t_data *data)
{
	add_history(data->line_from_read_before_trim);
	free(data->line_from_read_before_trim);
	parse_cmd_argv(data);
	free_cmd(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	data = (t_data){};
	make_envp(&data, envp);
	signal_catcher();
	if (ft_strnstr(argv[0], "minishell", ft_strlen(argv[0])) == NULL)
		sub_minishell(&data, argv);
	while (1)
	{
		data.line_from_read_before_trim = readline(PROG_NAME);
		if (!data.line_from_read_before_trim)
			sig_quit_catch(&data);
		if (!(*data.line_from_read_before_trim)
			|| *data.line_from_read_before_trim == '\n')
		{
			free(data.line_from_read_before_trim);
			continue ;
		}
		data.line_from_read = ft_strtrim(data.line_from_read_before_trim,
				" 	");
		if (*data.line_from_read)
			start_parse(&data);
	}
}
