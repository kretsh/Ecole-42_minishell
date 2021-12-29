/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:36:15 by utygett           #+#    #+#             */
/*   Updated: 2021/12/22 15:13:25 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_cmd	*ft_lstnew(void *content, void *content2)
{
	t_cmd	*new_list;

	new_list = malloc(sizeof(t_cmd));
	if (!new_list)
		return (NULL);
	new_list->pid = 1;
	new_list->next = NULL;
	new_list->cmd = content;
	new_list->value = content2;
	new_list->flags = (t_flags){};
	new_list->error_on_parsing = 0;
	new_list->prev = NULL;
	new_list->argv_for_cmd = NULL;
	new_list->start_list = NULL;
	return (new_list);
}
