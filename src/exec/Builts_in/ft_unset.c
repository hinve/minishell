/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matta <matta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:41:43 by matta             #+#    #+#             */
/*   Updated: 2024/10/16 16:21:31 by matta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void remove_env_var(t_env **env, const char *key)
{
    t_env *current = *env;
    t_env *previous = NULL;

    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            if (previous)
            {
                previous->next = current->next;
            }
            else
            {
                *env = current->next;
            }
            free(current->key);
            free(current->value);
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}

void    print_unset_error(const char *message)
{
    write(STDERR_FILENO, message, ft_strlen(message));
}

int ft_unset(t_cmd cmd, t_shell *data)
{
    int i = 1;
    char **argv = cmd.arg;

    if (!argv[1]) {
        print_unset_error("unset: not enough arguments\n");
        return (EXIT_FAILURE);
    }

    while (argv[i])
    {
        remove_env_var(&(data->env), argv[i]);
        i++;
    }

    return (EXIT_SUCCESS);
}