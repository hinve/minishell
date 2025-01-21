/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:57:09 by mjeannin          #+#    #+#             */
/*   Updated: 2025/01/21 18:13:29 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static int	execute_sys_bin(t_shell *data, t_cmd *cmd)
{
	if (!cmd->arg || cmd->arg[0] == '\0')
		return (127);
	if (cmd_is_dir(cmd->arg))
		return (127);
	data->path = get_cmd_path(data, cmd->arg);
	if (!data->path)
		return (127);
	if (execve(data->path, cmd->arg, data->env) == -1)
		errmsg_cmd("execve", NULL, strerror(errno), errno);
	return (1);
}

static int	execute_local_bin(t_shell *data, t_cmd *cmd)
{
	int	ret;

	ret = check_command_not_found(data, cmd);
	if (ret != 0)
		return (ret);
	if (execve(cmd->arg[0], cmd->arg, data->env) == -1)
		return (errmsg_cmd("execve", NULL, strerror(errno), errno));
	return (EXIT_FAILURE);
} */


void	executer(t_shell *data, t_cmd *current)
{
    if (!execute_builtin(data))
    {
        get_path(data, current);
        if (!data->path)
        {
            perror("Error: command not found");
            exit(127);
        }
        dup2(current->fdout, 1); // Redirect stdout to fdout
        close(current->fdout);   // Close fdout as it's now duplicated
        execve(data->path, current->arg, data->envp);
        perror("Error: execve failed");
        exit(127);
    }
}

void	restart_fds(int tmpin, int tmpout)
{
	dup2(tmpin, 0);
	dup2(tmpout, 1);
	close(tmpin);
	close(tmpout);
}

void handle_pipes(t_shell *data)
{
    int tmpin;
    int tmpout;
    int fdpipe[2];
    int i;
    t_cmd *current;

    tmpin = dup(0);
    tmpout = dup(1);
    current = data->cmd;

    if (current->fdin == -1)
        current->fdin = dup(tmpin);
    i = 0;
    while (current)
    {
        if (current->next)
        {
            pipe(fdpipe);
            current->fdout = fdpipe[1];
            current->next->fdin = fdpipe[0];
        }
/*         else
        {
            current->fdout = dup(tmpout);
        } */
        if (fork() == 0)
        {
            dprintf(2, "ping fd %d\n", current->fdout);
            if (current->fdin != -1)
            {
                dup2(current->fdin, 0);
                close(current->fdin);
                printf("ping fdin != -1\n");
            }
            if (current->fdout != -1)
            {
                dup2(current->fdout, 1);
                close(current->fdout);
                printf("ping fdout != -1\n");
            }
            executer(data, current);
            exit(0); // Ensure the child process exits after executing the command
        }

        if (current->fdin != -1)
            close(current->fdin);
        if (current->fdout != -1)
            close(current->fdout);

        current = current->next;
        i++;
    }

    for (i = 0; i < data->cmd_count; i++)
        waitpid(data->pid[i], &data->status, 0);

    data->status = WEXITSTATUS(data->status);
    restart_fds(tmpin, tmpout);
}
void	executor(t_shell *data)
{
	t_cmd	*current;
    
	count_commands(data);
	init_pid(data);
	current = data->cmd;
	if (!current)
		return ;
    if (data->cmd_count == 1)
        executer(data, current);
    else
        handle_pipes(data);
}