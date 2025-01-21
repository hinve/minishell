/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:58:24 by mjeannin          #+#    #+#             */
/*   Updated: 2025/01/21 15:53:11 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_swap(char **a, char **b)
{
	char	*aux;

	aux = *a;
	*a = *b;
	*b = aux;
}

void	count_commands(t_shell *data)
{
	t_cmd	*current_cmd;

	current_cmd = data->cmd;
	data->cmd_count = 0;
	while (current_cmd != NULL)
	{
		data->cmd_count++;
		current_cmd = current_cmd->next;
	}
}

void	init_pid(t_shell *data)
{
	data->pid = ft_calloc(sizeof(int), data->cmd_count);
	if (!data->pid)
		perror("Error: malloc failed");
}

void	end_processess(int *pids, int len)
{
	while (len)
		kill(pids[--len], SIGTERM);
	free(pids);
}
