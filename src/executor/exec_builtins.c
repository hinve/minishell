/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:01:24 by mjeannin          #+#    #+#             */
/*   Updated: 2025/02/04 14:50:16 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_shell *data, t_cmd *current)
{
	if (current->n_args == 0)
		return (0);
	if (ft_strcmp(current->arg[0], "echo") == 0)
		ft_echo(current);
	else if (ft_strcmp(current->arg[0], "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(current->arg[0], "cd") == 0)
		ft_cd(data);
	else if (ft_strcmp(current->arg[0], "export") == 0)
		ft_export(data);
	else if (ft_strcmp(current->arg[0], "unset") == 0)
		ft_unset(data);
	else if (ft_strcmp(current->arg[0], "env") == 0)
		ft_env(data->env);
	else if (ft_strcmp(current->arg[0], "exit") == 0)
		ft_exit(current);
	else
		return (0);
	return (1);
}

int is_builtin(t_cmd *cmd)
{

	if (cmd->n_args == 0)
		return (0);
	if (ft_strcmp(cmd->arg[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->arg[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->arg[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->arg[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->arg[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->arg[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->arg[0], "exit") == 0)
		return (1);
	else
		return (1);
}
