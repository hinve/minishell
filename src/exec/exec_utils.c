/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 00:02:42 by matta             #+#    #+#             */
/*   Updated: 2024/09/26 16:37:50 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    return NULL;
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

int is_var_declaration(t_shell data)
{
    const char *input = data.cmd->arg[1];
    const char *equal_sign;
    const char *ptr;

    if (input == NULL || *input == '\0')
        return (0);

    equal_sign = strchr(input, '=');
    if (equal_sign == NULL)
        return (0);

    if (equal_sign == input || *(equal_sign + 1) == '\0')
        return (0);

    ptr = input;
    while (ptr < equal_sign)
    {
        if (!isalnum(*ptr) && *ptr != '_')
            return (0);
        ptr++;
    }
    return (1);
}


