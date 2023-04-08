/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 13:33:53 by cowen             #+#    #+#             */
/*   Updated: 2021/12/23 14:07:54 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	check_flags(t_cmd *lst, t_cmd *line)
{
	if (lst->flags.pipe_in == NO && line->flags.pipe_in == YES)
		lst->flags.pipe_in = YES;
	if (lst->flags.pipe_out == NO && line->flags.pipe_out == YES
		&& line->c != '|')
		lst->flags.pipe_out = YES;
	if (lst->flags.redirect_d_left == NO && line->flags.redirect_d_left == YES)
		lst->flags.redirect_d_left = YES;
	if (lst->flags.redirect_left == NO && line->flags.redirect_left == YES)
		lst->flags.redirect_left = YES;
	if (lst->flags.redirect_right == NO && line->flags.redirect_right == YES)
		lst->flags.redirect_right = YES;
	if (lst->flags.redirect_d_right == NO
		&& line->flags.redirect_d_right == YES)
		lst->flags.redirect_d_right = YES;
	check_flag_part_two(lst, line);
}

void	check_flag_part_two(t_cmd *lst, t_cmd *line)
{
	if (lst->flags.parenthesis == NO && line->flags.parenthesis == YES)
		lst->flags.parenthesis = YES;
	if (lst->flags.env == NO && line->flags.env == YES)
		lst->flags.env = YES;
	if (lst->flags.and == NO && lst->flags.or == NO && line->flags.or)
		lst->flags.or = line->flags.or;
	if (lst->flags.or == NO && lst->flags.and == NO && line->flags.and)
		lst->flags.and = line->flags.and;
	if (lst->flags.wild_card == NO && line->flags.wild_card)
		lst->flags.wild_card = line->flags.wild_card;
	if (lst->error_on_parsing == NO && line->error_on_parsing)
		lst->error_on_parsing = line->error_on_parsing;
}

char	*check_home_token(char *str, t_data *data, t_cmd *line)
{
	if (!line)
	{
		free(str);
		return (search_env(ft_strdup("HOME"), data));
	}
	else if (line && line->c == '/')
	{
		free(str);
		return (search_env(ft_strdup("HOME"), data));
	}	
	return (str);
}

char	*check_wildcard(t_cmd **start, char *str)
{
	if (str)
	{
		if (ft_strncmp(str, "*\0", 2) == 0)
		{
			search_wild_cards(start);
			free(str);
			return (NULL);
		}
	}
	return (str);
}

char	*get_argv_if_env_exist(char *str, char *env)
{
	char	*buf_str;

	if (!str)
		str = ft_calloc(1, 1);
	if (!str)
		return (NULL);
	buf_str = ft_strjoin(str, env);
	if (!buf_str)
		return (NULL);
	free(env);
	free(str);
	return (buf_str);
}
