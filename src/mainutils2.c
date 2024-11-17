/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainutils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpino-mo <hpino-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:35:11 by hpino-mo          #+#    #+#             */
/*   Updated: 2024/11/17 17:07:05 by hpino-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_spaces(char *str_cmd)
{
	int	i;

	i = 0;
	while (str_cmd[i])
	{
		if (str_cmd[i] != ' ' && str_cmd[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	free_env_node(t_env *current_env)
{
	free(current_env->key);
	free(current_env->value);
	free(current_env);
}

void	clear_env_structs(t_env **env, t_env **vars)
{
	t_env	*current_env;
	t_env	*next_env;

	current_env = *env;
	while (current_env != NULL)
	{
		next_env = current_env->next;
		free_env_node(current_env);
		current_env = next_env;
	}
	*env = NULL;
	current_env = *vars;
	while (current_env != NULL)
	{
		next_env = current_env->next;
		free_env_node(current_env);
		current_env = next_env;
	}
	*vars = NULL;
}

void	free_token_node(t_token *current)
{
	free(current);
}

void	clear_structs(t_token **token, t_cmd **cmd)
{
	t_token	*current;
	t_cmd	*current_cmd;
	t_cmd	*next_cmd;
	t_token	*next;

	current = *token;
	while (current != NULL)
	{
		next = current->next;
		free_token_node(current);
		current = next;
	}
	current_cmd = *cmd;
	while (current_cmd != NULL)
	{
		if (current_cmd->fdin != -1)
			close(current_cmd->fdin);
		if (current_cmd->fdout != -1)
			close(current_cmd->fdout);
		next_cmd = current_cmd->next;
		free(current_cmd);
		current_cmd = next_cmd;
	}
	*cmd = NULL;
	*token = NULL;
}
