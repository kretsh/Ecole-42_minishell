/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils_third.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 16:03:12 by cowen             #+#    #+#             */
/*   Updated: 2021/12/23 16:03:32 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	get_cmd_and_argv_from_line(t_data *data, t_cmd **line)
{
	if (*line)
		get_cmd(*line, &data->cmd_start, data);
}

void	checking_after_parsing(t_cmd *new_list, t_cmd *ln, char *str, int *argv)
{
	if (new_list->flags.wild_card == 1)
		str = check_wildcard(&new_list->start_list, str);
	if (str)
		ft_lstadd_back(&new_list->start_list, ft_lstnew(NULL, str));
	if (ln)
		*argv = ln->flags.argv;
}

char	*get_cmd_if_argv_doesnt_exist(char *str, t_cmd *ln, t_cmd *new_list)
{
	if (!str && (ln->flags.d_quotes == YES
			|| ln->flags.quotes == YES)
		&& (ln->flags.redirect_right == NO
			&& ln->flags.redirect_d_right == NO
			&& ln->flags.redirect_left == NO
			&& ln->flags.redirect_d_left == NO))
	{
		str = ft_calloc(1, 1);
		check_flags(new_list, ln);
		return (str);
	}
	check_flags(new_list, ln);
	return (str);
}	
