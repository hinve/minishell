/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:33:54 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/02 18:15:12 by mjeannin         ###   ########.fr       */
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

void	get_path(t_shell *data, t_cmd *current)
{
	char	**paths;
	char	*temp;
	int		i;

	access_cmd(data);
	if (data->path)
		return ;
	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		return ;
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		data->path = ft_strjoin(temp, current->arg[0]);
		free(temp);
		if (access(data->path, F_OK) == 0)
		{
			free_split(paths);
			return ;
		}
		free(data->path);
		data->path = NULL;
		i++;
	}
	free_split(paths);
	data->path = NULL;
}
