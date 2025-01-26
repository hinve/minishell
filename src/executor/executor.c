/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:57:09 by mjeannin          #+#    #+#             */
/*   Updated: 2025/01/26 13:50:10 by mjeannin         ###   ########.fr       */
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


void exec_bin(t_shell *data, t_cmd *current)
{

    execve(data->path, current->arg, data->envp);
    
}

void	handle_bin(t_shell *data, t_cmd *current)
{
    if (execute_builtin(data))
    {
        get_path(data, current);
        if (!data->path)
        {
            perror("Error: command not found");
            exit(127);
        }
        exec_bin(data, current);
        perror("Error: execve failed");
    	exit(127);
    }
	exit(0);
}

void	close_fds(int *p_fd)
{
	close(p_fd[0]);
	close(p_fd[1]);
}

void handle_pipe_out(t_shell *data, t_cmd *current)
{
		pid_t	pid;
	int		status;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		return ;
	pid  = fork;
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (dup2(p_fd[1], 1) != 1)
			return ;
		close_fds(p_fd);
		handle_bin(data, current);
	}
	close_fds(p_fd);
}

void	handle_pipe_in(t_shell *data, t_cmd *current)
{
	pid_t	pid;
	int		status;
	int		p_fd[2];

	if (pipe(p_fd) == -1)
		return ;
	pid  = fork;
	if (pid == -1)
		return ;
	if (pid == 0)
	{
		if (dup2(p_fd[1], 1) != 1)
			return ;
		close_fds(p_fd);
		handle_bin(data, current);
	}
	if (dup2(p_fd[0], 0) != 0)
		return ;
	close_fds(p_fd);
}

void	executor(t_shell *data)
{
	t_cmd	*current = data->cmd;

	while (current)
	{
		handle_pipe_in(data, current);
		if (current->next)
			current = current->next;
	}
		handle_pipe_out(data, current);
	waitpid(-1, &data->status, WUNTRACED);
}