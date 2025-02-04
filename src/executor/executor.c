/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:57:09 by mjeannin          #+#    #+#             */
/*   Updated: 2025/02/04 16:14:28 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void redirection(t_cmd *current, int tmpout, int last_cmd)
{
    int fdpipe[2];

    if (dup2(current->fdin, 0) == -1)
    {
        perror("Error: dup2 failed for input redirection");
        exit(1);
    }
    close(current->fdin);

    if (last_cmd)
    {
        if (current->fdout == -1)
        {
            current->fdout = dup(tmpout);
            if (current->fdout == -1)
            {
                perror("Error: dup failed for output redirection");
                exit(1);
            }
        }
    }
    else
    {
        if (pipe(fdpipe) == -1)
        {
            perror("Error: pipe failed");
            exit(1);
        }
        current->next->fdin = fdpipe[0];
        if (current->fdout == -1)
        {
            current->fdout = fdpipe[1];
        }
        else
        {
            close(fdpipe[1]);
        }
    }
    if (dup2(current->fdout, 1) == -1)
    {
        perror("Error: dup2 failed for output redirection");
        exit(1);
    }
    close(current->fdout);
}

void executer(t_shell *data, t_cmd *current, int i)
{
    if (!execute_builtin(data, current))
    {
        data->pid[i] = fork();
        if (data->pid[i] == 0)
        {
            get_path(data, current);
            if (!data->path)
            {
                perror("Error: command not found");
                exit(127);
            }
            execve(data->path, current->arg, data->envp);
            perror("Error: execve failed");
            exit(127);
        }
        else if (data->pid[i] < 0)
            perror("Error: fork failed");
        else
        {
            if (current != NULL)
                close(current->fdout);
        }
    }
}

void restart_fds(int tmpin, int tmpout)
{
    dup2(tmpin, 0);
    dup2(tmpout, 1);
    close(tmpin);
    close(tmpout);
}

void executor(t_shell *data)
{
    int tmpin;
    int tmpout;
    int i;
    t_cmd *current;

    i = -1;
    count_commands(data);
    init_pid(data);
    current = data->cmd;
    if (!current)
        return;
    tmpin = dup(0);
    tmpout = dup(1);
    if (current->fdin == -1)
        current->fdin = dup(tmpin);
    while (++i < data->cmd_count)
    {
        redirection(current, tmpout, data->cmd_count - 1 == i);
        executer(data, current, i);
        current = current->next;
    }
    waitpid(data->pid[data->cmd_count - 1], &data->status, 0);
    data->status = WEXITSTATUS(data->status);
    end_processess(data->pid, data->cmd_count - 1);
    restart_fds(tmpin, tmpout);
}