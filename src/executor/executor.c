/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:57:09 by mjeannin          #+#    #+#             */
/*   Updated: 2025/01/15 16:40:26 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirection(t_cmd *current, int tmpout, int last_cmd)
{
	int	fdpipe[2];

	dup2(current->fdin, 0);
	close(current->fdin);
	if (last_cmd)
	{
		if (current->fdout == -1)
			current->fdout = dup(tmpout);
	}
	else
	{
		pipe(fdpipe);
		current->next->fdin = fdpipe[0];
		if (current->fdout == -1)
			current->fdout = fdpipe[1];
		else
			close(fdpipe[1]);
	}
	dup2(current->fdout, 1);
	close(current->fdout);
}

void	executer(t_shell *data, t_cmd *current, int i)
{
	if (!execute_builtin(data))
	{
		data->pid[i] = fork();
		if (data->pid[i] == 0)
		{
			get_path(data, current);
			if (!data->path)
			{
				printf("Error: command not found: %s\n", current->arg[0]);
				exit(127);
			}
			execve(data->path, current->arg, data->envp);
			perror("Error: execve failed");
			exit(127);
		}
		else if (data->pid[i] < 0)
		{
			perror("Error: fork failed");
		}
	}
}

void	restart_fds(int tmpin, int tmpout)
{
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
}

void	executor(t_shell *data)
{
	int		tmpin;
	int		tmpout;
	int		fdpipe[2];
	t_cmd	*current;
	int		i;

	tmpin = dup(0);
	tmpout = dup(1);
	current = data->cmd;
	i = 0;
	while (current)
	{
		dup2(current->fdin, 0);
		close(current->fdin);
		if (current->next)
		{
			pipe(fdpipe);
			current->next->fdin = fdpipe[0];
			if (current->fdout == -1)
				current->fdout = fdpipe[1];
			else
				close(fdpipe[1]);
		}
		dup2(current->fdout, 1);
		close(current->fdout);
		executer(data, current, i);
		current = current->next;
		i++;
	}
	restart_fds(tmpin, tmpout);
}
