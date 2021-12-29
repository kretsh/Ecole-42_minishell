/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 23:58:14 by cowen             #+#    #+#             */
/*   Updated: 2021/12/23 16:20:31 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	export_no_arguments(t_cmd **list)
{
	t_cmd	*temp;

	temp = *list;
	while (temp)
	{
		printf("declare -x %s", temp->cmd);
		if (*(temp->value))
			printf("\"%s\"\n", temp->value);
		else
			printf("\n");
		temp = temp->next;
	}
}

int	write_export_error(t_data *data, char *argv)
{
	write(2, "export: '", 9);
	write(2, argv, ft_strlen(argv));
	write(2, "': not a valid identifier\n", 26);
	data->return_value = 1 * 256;
	return (1);
}

int	check_argv_for_existing_without_equal(char *argv, t_cmd **list)
{
	t_cmd	*temp;

	temp = *list;
	while (temp)
	{
		if (ft_strncmp(argv, temp->cmd, ft_strlen(argv)) == 0)
			return (YES);
		temp = temp->next;
	}
	return (NO);
}

void	new_chain(t_cmd *temp, t_cmd **temp2)
{
	*temp2 = temp;
	temp = temp->next;
	(*temp2)->next = temp->next;
	free(temp->cmd);
	free(temp->value);
	free(temp);
}

void	write_unset(t_data *data, char *argv)
{
	write(2, "unset: '", 9);
	write(2, argv, ft_strlen(argv));
	write(2, "': not a valid identifier\n", 26);
	data->return_value = 1 * 256;
}
