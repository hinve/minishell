/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:02:46 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/28 11:05:25 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_lst_search(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			return (env);
		}
		env = env->next;
	}
	return (NULL);
}

static int	update_pwd_oldpwd(t_env *env, const char *key, const char *value)
{
	t_env	*temp_env;

	temp_env = env_lst_search(env, key);
	if (temp_env)
	{
		if (temp_env->value)
		{
			free(temp_env->value);
		}
		temp_env->value = ft_strdup(value);
		if (!temp_env->value)
		{
			return (0);
		}
	}
	return (1);
}

static char	*get_home_or_oldpwd(t_shell *data, char *key, char *old_pwd)
{
	char	*path;

	path = get_cd_value(data->env, key);
	if (!path)
	{
		free(old_pwd);
		perror("Error: Environment variable not found");
	}
	return (path);
}

static char	*get_pwd(t_shell *data, char *old_pwd)
{
	char	*path;

	path = NULL;
	if (data->cmd->n_args == 1 || !ft_strncmp(data->cmd->arg[1], "~", 1))
		path = get_home_or_oldpwd(data, "HOME", old_pwd);
	else if (!ft_strncmp(data->cmd->arg[1], "-", 1))
		path = get_home_or_oldpwd(data, "OLDPWD", old_pwd);
	else
	{
		path = ft_strdup(data->cmd->arg[1]);
		if (!path)
		{
			free(old_pwd);
			perror("Error: Memory allocation failed");
		}
	}
	return (path);
}

void	ft_cd(t_shell *data)
{
	char	*path;
	char	*old_pwd;

	old_pwd = get_current_directory();
	path = get_current_directory();
	if (!old_pwd)
		return (perror("Error: Failed to get current directory"), (void)0);
	path = get_pwd(data, old_pwd);
	if (!path)
		return (free(old_pwd), (void)0);
	if (chdir(path) != 0)
	{
		perror("chdir failed");
		return (free(old_pwd), free(path), (void)0);
	}
	if (!update_pwd_oldpwd(data->env, "OLDPWD", old_pwd) || \
	!update_pwd_oldpwd(data->env, "PWD", path))
		perror("Error: updating environment variables");
	free(old_pwd);
	free(path);
}
