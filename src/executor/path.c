/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:33:54 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/03 14:33:49 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static void	access_cmd(t_shell *data)
{
	if (access(data->cmd->arg[0], X_OK) == 0)
	{
		data->path = ft_strdup(data->cmd->arg[0]);
		return ;
	}
}

static char	*join_paths(const char *path, const char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(path, "/");
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}

static int	check_paths(char **paths, t_shell *data, t_cmd *current)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		data->path = join_paths(paths[i], current->arg[0]);
		if (access(data->path, F_OK) == 0)
		{
			free_split(paths);
			return (1);
		}
		free(data->path);
		data->path = NULL;
		i++;
	}
	return (0);
}

void	get_path(t_shell *data, t_cmd *current)
{
	char	**paths;

	paths = ft_split(getenv("PATH"), ':');
	access_cmd(data);
	if (data->path)
		return ;
	if (!paths)
		return ;
	if (!check_paths(paths, data, current))
		free_split(paths);
}
