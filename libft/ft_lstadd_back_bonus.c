/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 15:44:51 by utygett           #+#    #+#             */
/*   Updated: 2021/12/06 19:17:05 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*b_list;

	b_list = *lst;
	if (!(*lst))
	{
		*lst = new;
		new->prev = NULL;
	}
	else
	{
		while (b_list->next)
		{
			b_list = b_list->next;
		}
		new->prev = b_list;
		b_list->next = new;
	}
}
