/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matta <matta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 00:02:42 by matta             #+#    #+#             */
/*   Updated: 2024/10/21 12:42:15 by matta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     is_key_in_env(t_shell data)
{
    t_env *currentenv = data.env;
    t_env *currentvar = data.var;

    while (currentenv)
    {
        if (ft_strcmp(currentenv->key, data.cmd->arg[0]) == 0)
        {
            return (1);
        }
        currentenv = currentenv->next;
    }
    while (currentvar)
    {
        if (ft_strcmp(currentvar->key, data.cmd->arg[0]) == 0)
        {
            return (1);
        }
        currentvar = currentvar->next;
    }
    return (0);
}

char *get_env_value(t_env *env, const char *key)
{
    t_env *current = env;
    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current->value;
        }
        current = current->next;
    }
    return (NULL);
}

int is_bin(t_shell data)
{
    t_cmd *currentcmd = data.cmd;
    if (ft_strcmp(currentcmd->arg[0], "pwd") == 0 || ft_strcmp(currentcmd->arg[0], "env") == 0 
        || ft_strcmp(currentcmd->arg[0], "echo") == 0 || ft_strcmp(currentcmd->arg[0], "export") == 0 
        || ft_strcmp(currentcmd->arg[0], "man") == 0 || ft_strcmp(currentcmd->arg[0], "cd") == 0 || 
        ft_strcmp(currentcmd->arg[0], "exit") == 0)
        return (1);
    return (0);
}


