/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:02:46 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/05 11:06:04 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_env *env_lst_search(t_env *env, const char *key)
{
    while (env)
    {
        if (!ft_strncmp(env->key, key, ft_strlen(key) + 1))
            return (env);
        env = env->next;
    }
    return (NULL);
}

static int update_pwd_oldpwd(t_env *env, const char *key, const char *value)
{
    t_env *temp_env;

    temp_env = env_lst_search(env, key);
    if (temp_env)
    {
        if (temp_env->value)
        {
            free(temp_env->value);
            temp_env->value = NULL;
        }
        temp_env->value = ft_strdup(value);
        if (!temp_env->value)
            return (0);
    }
    return (1);
}

static char *get_pwd(t_shell *data, char *path, char *old_pwd)
{
    if (data->cmd->n_args == 1 || !ft_strncmp(data->cmd->arg[1], "~", 1))
    {
        path = get_cd_value(data->env, "HOME");
        if (!path)
        {
            free(old_pwd);
            perror("Error: HOME not found");
            return (NULL);
        }
    }
    else if (!ft_strncmp(data->cmd->arg[1], "-", 1))
    {
        path = get_cd_value(data->env, "OLDPWD");
        if (!path)
        {
            free(old_pwd);
            perror("Error: OLDPWD not found");
            return (NULL);
        }
    }
    else
    {
        path = ft_strdup(data->cmd->arg[1]);
        if (!path)
        {
            free(old_pwd);
            perror("Error: Memory allocation failed");
            return (NULL);
        }
    }
    return (path);
}

void ft_cd(t_shell *data)
{
    char *path;
    char *old_pwd;

    old_pwd = get_current_directory();
    if (!old_pwd)
    {
        perror("Error: Failed to get current directory");
        return;
    }

    path = get_pwd(data, NULL, old_pwd);
    if (!path)
        return;

    if (chdir(path) != 0)
    {
        perror("chdir failed");
        free(old_pwd);
        free(path);
        return;
    }

    if (!update_pwd_oldpwd(data->env, "OLDPWD", old_pwd) || !update_pwd_oldpwd(data->env, "PWD", path))
    {
        perror("Error: Failed to update PWD or OLDPWD");
    }

    free(old_pwd);
    free(path);
}