/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:44:24 by matteo            #+#    #+#             */
/*   Updated: 2024/11/17 15:32:51 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_echo(t_shell *data)
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
		if (write(STDOUT_FILENO, currentcmd->arg[i], ft_strlen(currentcmd->arg[i])) == -1)
		{
			perror("echo");
			return (status(data, 1));
		}
		if (i < currentcmd->n_args - 1)
		{
			if (write(STDOUT_FILENO, " ", 1) == -1)
			{
				perror("echo");
				return (status(data, 1));
			}
		}
		i++;
	}
	if (newline)
	{
		if (write(STDOUT_FILENO, "\n", 1) == -1)
		{
			perror("echo");
			return (status(data, 1));
		}
	}
	return (status(data, 0));
}