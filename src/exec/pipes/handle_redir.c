/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matteo <matteo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 00:05:03 by matteo            #+#    #+#             */
/*   Updated: 2024/11/21 00:39:11 by matteo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_redirections(t_cmd *cmd)
{
    int in_fd;
    int out_fd;

    if (cmd->fdin)
    {
        in_fd = open(cmd->fdin, O_RDONLY);
        if (in_fd < 0)
        {
            perror("open input file");
            exit(EXIT_FAILURE);
        }
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
    }

    if (cmd->fdout)
    {
        if (cmd->append)
        {
            out_fd = open(cmd->fdout, O_WRONLY | O_CREAT | O_APPEND, 0644);
        }
        else
        {
            out_fd = open(cmd->fdout, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }
        if (out_fd < 0)
        {
            perror("open output file");
            exit(EXIT_FAILURE);
        }
        dup2(out_fd, STDOUT_FILENO);
        close(out_fd);
    }
}

void handle_pipes(t_shell *data)
{
    t_cmd *current = data->cmd;
    int pipe_fd[2];
    pid_t pid;

    while (current)
    {
        if (current->next)
        {
            if (pipe(pipe_fd) == -1)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
            current->fdout = pipe_fd[1];
            current->next->fdin = pipe_fd[0];
        }
        pid = fork();
        if (pid == 0)
        {
            if (current->fdin != STDIN_FILENO)
            {
                dup2(current->fdin, STDIN_FILENO);
                close(current->fdin);
            }
            if (current->fdout != STDOUT_FILENO)
            {
                dup2(current->fdout, STDOUT_FILENO);
                close(current->fdout);
            }
            handle_redirections(current);
            execve(current->arg[0], current->arg, NULL);
            perror("execve");
            exit(EXIT_FAILURE);
        }
        else if (pid > 0)
        {
            waitpid(pid, NULL, 0);
            if (current->fdout != STDOUT_FILENO)
            {
                close(current->fdout);
            }
            if (current->fdin != STDIN_FILENO)
            {
                close(current->fdin);
            }
        }
        else
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        current = current->next;
    }
}