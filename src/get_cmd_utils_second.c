/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils_second.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 16:01:12 by cowen             #+#    #+#             */
/*   Updated: 2021/12/23 16:02:24 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*now_str_before(char *str, char c)
{
	str = malloc(2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

int	parsing_init(t_cmd *ln, int *cmd, t_cmd **new_list, int *argv)
{
	if (!ln)
		return (1);
	if (ln->flags.start == 1)
		*cmd = 0;
	*new_list = ft_lstnew_char('c');
	*argv = ln->flags.argv;
	return (0);
}

void	parenthesis_parsing(t_cmd **ln, char **str, int *cmd)
{
	while (*ln && (*ln)->flags.parenthesis)
	{
		*str = char_add_to_str(*str, (*ln)->c);
		*cmd = (*ln)->flags.cmd;
		*ln = (*ln)->next;
	}
}

void	str_init_in_parsing(t_cmd **ln, char **str, t_data *data,
	t_cmd *new_list)
{
	t_cmd	*temp;

	temp = *ln;
	*str = get_argv(*str, temp, data, &new_list->flags.redirect_filename);
	if ((*ln)->flags.wild_card == 2)
		*str = check_home_token(*str, data, (*ln)->next);
	*ln = (*ln)->next;
}

void	cmd_init_in_parsing(t_cmd *ln, int *cmd)
{
	if (ln)
		*cmd = ln->flags.cmd;
}
