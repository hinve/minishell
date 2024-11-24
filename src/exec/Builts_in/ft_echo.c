/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:44:24 by matteo            #+#    #+#             */
/*   Updated: 2024/11/21 15:36:27 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_output(const char *str)
{
	if (write(STDOUT_FILENO, str, ft_strlen(str)) == -1)
	{
		perror("echo");
		return (1);
	}
	return (0);
}

int	write_space(void)
{
	if (write(STDOUT_FILENO, " ", 1) == -1)
	{
		perror("echo");
		return (1);
	}
	return (0);
}

int	ft_echo(t_shell *data)
{
	t_cmd	*currentcmd;
	int		i;
	int		newline;

	currentcmd = data->cmd;
	i = 1;
	newline = 1;
	if (currentcmd->n_args > 1 && ft_strcmp(currentcmd->arg[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}
	while (i < currentcmd->n_args)
	{
		if (write_output(currentcmd->arg[i]) || \
			(i < currentcmd->n_args - 1 && write_space()))
			return (status(data, 1));
		i++;
	}
	if (newline && write_output("\n"))
		return (status(data, 1));
	return (status(data, 0));
}
