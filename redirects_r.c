/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 20:02:46 by cowen             #+#    #+#             */
/*   Updated: 2021/12/22 20:13:34 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	check_redirect_r(t_cmd *lst)
{
	static int	redirect_d_right;
	static int	redirect_right;

	null_redir_r(lst, &redirect_right, &redirect_d_right, 1);
	if ((lst->flags.quotes == NO)
		&& (lst->flags.d_quotes == NO) && lst->c == '>')
	{
		if (lst->prev && lst->prev->c == '>' && lst->c == '>')
			search_for_double_redirect(lst, &redirect_d_right, &redirect_right);
		else if (((lst->prev && lst->prev->c != '>') || !lst->prev)
			&& lst->c == '>')
			search_for_redirect(lst, &redirect_right);
	}
	if ((lst->flags.quotes == NO) && (lst->flags.d_quotes == NO)
		&& (redirect_d_right == YES || redirect_right == YES)
		&& lst->c == ' ')
		null_redir_r(lst, &redirect_right, &redirect_d_right, 2);
	init_redir_r(lst, redirect_right, redirect_d_right);
}

void	search_for_double_redirect(t_cmd *lst, int *right_red_d, int *right_red)
{
	int			cmd;
	t_cmd		*buf;

	cmd = lst->flags.cmd;
	buf = lst->prev;
	while (buf && cmd == buf->flags.cmd)
	{
		if (buf->flags.redirect_d_right == 1)
			buf->flags.remove = 1;
		buf = buf->prev;
	}
	*right_red_d = YES;
	*right_red = NO;
	lst->prev->flags.redirect_right = NO;
	lst->flags.remove = YES;
	lst->flags.argv++;
}	

void	search_for_redirect(t_cmd *lst, int *redirect_right)
{
	int			cmd;
	t_cmd		*buf;

	cmd = lst->flags.cmd;
	buf = lst->prev;
	while (buf && cmd == buf->flags.cmd)
	{
		if (buf->flags.redirect_right == 1)
			buf->flags.remove = 1;
		buf = buf->prev;
	}
	lst->flags.argv++;
	*redirect_right = YES;
	lst->flags.remove = YES;
}

void	null_redir_r(t_cmd *lst, int *redirect_r, int *redirect_d_r, int flag)
{
	if (lst->flags.start == 1 && flag == 1)
	{
		*redirect_r = 0;
		*redirect_d_r = 0;
	}
	else if (lst->prev->c != '>' && flag == 2)
	{
		*redirect_r = 0;
		*redirect_d_r = 0;
	}
}

void	init_redir_r(t_cmd *lst, int redirect_right, int redirect_d_right)
{
	lst->flags.redirect_d_right = redirect_d_right;
	lst->flags.redirect_right = redirect_right;
}
