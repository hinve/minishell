/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 11:01:24 by mjeannin          #+#    #+#             */
/*   Updated: 2025/01/27 12:25:19 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_shell *data, t_cmd *current)
{
	if (current->n_args == 0)
		return (0);
	if (ft_strcmp(current->arg[0], "echo") == 0)
		return (ft_echo(current), 1);
	else if (ft_strcmp(current->arg[0], "pwd") == 0)
		return (ft_pwd(), 1);
	else if (ft_strcmp(current->arg[0], "cd") == 0)
		return (ft_cd(data), 1);
	else if (ft_strcmp(current->arg[0], "export") == 0)
		return (ft_export(data), 1);
	else if (ft_strcmp(current->arg[0], "unset") == 0)
		return (ft_unset(data), 1);
	else if (ft_strcmp(current->arg[0], "env") == 0)
		return (ft_env(data->env), 1);
	else if (ft_strcmp(current->arg[0], "exit") == 0)
		return (ft_exit(current), 1);
	else
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
