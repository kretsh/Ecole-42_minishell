/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:50:05 by utygett           #+#    #+#             */
/*   Updated: 2021/12/01 20:10:07 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_cmd	*ft_lstmap(t_cmd *lst, void *(*f)(void *), void (*del)(void *))
{
	t_cmd	*list;
	t_cmd	*flist;

	list = 0;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{	
		flist = ft_lstnew(f(lst->cmd), f(lst->value));
		if (!flist || flist->cmd == NULL || flist->value == NULL)
		{
			if (del)
				ft_lstclear(&list, del);
			return (NULL);
		}
		ft_lstadd_back(&list, flist);
		lst = lst->next;
	}
	return (list);
}
