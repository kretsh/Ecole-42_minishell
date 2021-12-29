/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 16:33:10 by utygett           #+#    #+#             */
/*   Updated: 2021/12/01 20:06:53 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_cmd **lst, void (*del)(void*))
{	
	t_cmd	*b_lst;

	if (lst)
	{
		while (*lst)
		{
			b_lst = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = b_lst;
		}
	}
}
