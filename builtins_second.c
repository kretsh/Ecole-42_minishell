/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_second.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cowen <cowen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 17:26:59 by cowen             #+#    #+#             */
/*   Updated: 2021/12/21 19:25:39 by cowen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	exit_with_exit(t_data *data, char **argv)
{
	int			i;
	long int	res;
	int			sign;

	sign = 1;
	res = 0;
	i = 0;
	while (argv && argv[i])
		i++;
	if (i > 2)
	{
		exit_write(1, data);
		return ;
	}
	else if (i == 1)
		exit_write(2, data);
	i = check_minus(argv[1][0]);
	if (i == 1)
		sign = -1;
	while ('0' <= argv[1][i] && argv[1][i] <= '9')
		res = (res * 10) + (argv[1][i++] - 48);
	if (argv[1][i] != '\0')
		exit_write(3, data);
	data->return_value = res * sign;
	exit_write(2, data);
}

int	check_minus(char minus)
{
	if (minus == '-')
		return (1);
	else
		return (0);
}

void	exit_write(int i, t_data *data)
{	
	if (i == 1)
	{
		write(2, "exit\n", 5);
		write(2, "exit: too many arguments\n", 26);
		data->return_value = 256;
	}
	else if (i == 2)
	{
		write(2, "exit\n", 5);
		exit(data->return_value);
	}
	else if (i == 3)
	{
		write(2, "exit\n", 5);
		write(2, "exit: numeric argument required\n", 33);
		data->return_value = 255;
		exit(data->return_value);
	}
}
