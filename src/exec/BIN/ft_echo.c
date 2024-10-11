/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matta <matta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:44:24 by matteo            #+#    #+#             */
/*   Updated: 2024/10/10 21:53:42 by matta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(t_shell *data)
{
    t_cmd *currentcmd = data->cmd;
    int i = 1;
    int newline = 1;

    if (currentcmd->n_args > 1 && ft_strcmp(currentcmd->arg[1], "-n") == 0)
    {
        newline = 0;
        i = 2;
    }
    while (i < currentcmd->n_args)
    {
        write(STDOUT_FILENO, currentcmd->arg[i], ft_strlen(currentcmd->arg[i]));
        if (i < currentcmd->n_args - 1)
        {
            write(STDOUT_FILENO, " ", 1);
        }
        i++;
    }
    if (newline)
    {
        write(STDOUT_FILENO, "\n", 1);
    }
}