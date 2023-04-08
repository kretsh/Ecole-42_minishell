/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: utygett <utygett@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 12:47:03 by utygett           #+#    #+#             */
/*   Updated: 2021/12/23 12:47:52 by utygett          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*cl_dir_and_ret_dir(DIR *dir, char *str)
{
	closedir(dir);
	return (str);
}

char	*search_cmd_paths(t_data *data, char *cmd)
{
	DIR				*dir;
	struct dirent	*ent;
	int				i;

	i = -1;
	if (!data->paths_to_binary)
		return (NULL);
	while (data->paths_to_binary[++i])
	{
		dir = opendir(data->paths_to_binary[i]);
		if (dir != NULL)
		{
			while (1)
			{
				ent = readdir(dir);
				if (!ent)
					break ;
				if (!ft_strcmp(ent->d_name, cmd))
					return (cl_dir_and_ret_dir(dir, data->paths_to_binary[i]));
			}
			closedir(dir);
		}
	}
	return (NULL);
}

void	search_wild_cards(t_cmd **start)
{
	DIR				*dir;
	struct dirent	*ent;
	char			path_currend_dir[PATH_MAX];

	dir = opendir(getcwd(path_currend_dir, PATH_MAX));
	if (dir != NULL)
	{
		while (1)
		{
			ent = readdir(dir);
			if (!ent)
				break ;
			if (*ent->d_name != '.')
				ft_lstadd_back(start, ft_lstnew(NULL, ft_strdup(ent->d_name)));
		}
		closedir(dir);
	}
}
