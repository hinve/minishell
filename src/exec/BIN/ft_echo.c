/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matteo <matteo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:44:24 by matteo            #+#    #+#             */
/*   Updated: 2024/09/13 10:44:25 by matteo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(t_cmd cmd)
{
    int i = 1;
    int newline = 1;

    if (cmd.n_args > 1 && strcmp(cmd.arg[1], "-n") == 0)
    {
        newline = 0;
        i = 2;
    }
    while (i < cmd.n_args)
    {
        write(STDOUT_FILENO, cmd.arg[i], ft_strlen(cmd.arg[i]));
        if (i < cmd.n_args - 1)
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