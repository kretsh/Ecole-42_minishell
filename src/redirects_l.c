/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_l.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 20:08:55 by cowen             #+#    #+#             */
/*   Updated: 2021/12/22 21:01:51 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	check_redirect_l(t_cmd *lst)
{
	static int	redirect_d_left;
	static int	redirect_left;

	null_redir_l(lst, &redirect_left, &redirect_d_left, 1);
	if ((lst->flags.quotes == NO)
		&& (lst->flags.d_quotes == NO) && lst->c == '<')
	{
		if (lst->prev && lst->prev->c == '<' && lst->c == '<')
			parse_heredoc(lst, &redirect_left, &redirect_d_left);
		else if (lst->prev && lst->prev->c != '<'
			&& lst->c == '<')
			search_for_redirect_l(lst, &redirect_left);
	}
	if ((lst->flags.quotes == NO) && (lst->flags.d_quotes == NO)
		&& (redirect_d_left == YES
			|| redirect_left == YES) && lst->c == ' ')
		null_redir_l(lst, &redirect_left, &redirect_d_left, 2);
	init_redir_l(lst, redirect_left, redirect_d_left);
}

void	null_redir_l(t_cmd *lst, int *redirect_l, int *redirect_d_l, int flag)
{
	if (lst->flags.start == 1 && flag == 1)
	{
		*redirect_l = 0;
		*redirect_d_l = 0;
	}
	else if (lst->prev->c != '<' && flag == 2)
	{
		*redirect_l = 0;
		*redirect_d_l = 0;
	}
}

void	init_redir_l(t_cmd *lst, int redirect_left, int redirect_d_left)
{
	lst->flags.redirect_d_left = redirect_d_left;
	lst->flags.redirect_left = redirect_left;
}

void	parse_heredoc(t_cmd *lst, int *redirect_left, int *redirect_d_left)
{
	*redirect_d_left = YES;
	*redirect_left = NO;
	lst->prev->flags.redirect_left = NO;
	lst->flags.remove = YES;
	lst->flags.argv++;
}

void	search_for_redirect_l(t_cmd *lst, int *redirect_left)
{
	int			cmd;
	t_cmd		*buf;

	*redirect_left = YES;
	cmd = lst->flags.cmd;
	buf = lst->prev;
	while (buf && cmd == buf->flags.cmd)
	{
		if (buf->flags.redirect_left == 1)
			buf->flags.remove = 1;
		buf = buf->prev;
	}
	lst->flags.remove = YES;
	lst->flags.argv++;
}
