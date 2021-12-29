/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:51:49 by utygett           #+#    #+#             */
/*   Updated: 2021/12/01 20:03:42 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_cmd **lst, t_cmd *new)
{
	if (lst && !(*lst))
		*lst = new;
	else if (lst)
	{
		new->next = *lst;
		*lst = new;
	}
}
