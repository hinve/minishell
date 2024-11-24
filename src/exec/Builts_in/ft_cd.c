/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:36:46 by mjeannin          #+#    #+#             */
/*   Updated: 2024/11/21 15:42:21 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_env_var(t_env **env, const char *key, const char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
	{
		printf("cd: memory allocation error\n");
		return (0);
	}
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	if (!new_node->key || !new_node->value)
	{
		printf("cd: memory allocation error\n");
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (0);
	}
	new_node->next = *env;
	*env = new_node;
	return (0);
}

int	update_env_var(t_env **env, const char *key, const char *value)
{
	t_env	*current;

	current = *env;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			if (!current->value)
				printf("cd: memory allocation error\n");
			return (0);
		}
		current = current->next;
	}
	return (add_env_var(env, key, value));
}

int	change_directory(const char *path)
{
	if (chdir(path) != 0)
	{
		printf("cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	return (0);
}

int	ft_cd(t_shell *data)
{
	char	*path;
	char	cwd[1024];

	if (data->cmd->n_args < 2 || ft_strlen(data->cmd->arg[1]) == 0)
		return (status(data, 0));
	path = data->cmd->arg[1];
	if (change_directory(path))
		return (status(data, 1));
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		update_env_var(&(data->env), "PWD", cwd);
		return (status(data, 0));
	}
	else
	{
		printf("cd: error retrieving current directory: %s\n", strerror(errno));
		return (status(data, 1));
	}
}
