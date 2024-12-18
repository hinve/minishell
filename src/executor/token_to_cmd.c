/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:39:31 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/18 14:02:17 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cmd_to_list(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*temp;

	if (!new_cmd)
		return ;
	if (*head == NULL)
		*head = new_cmd;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_cmd;
	}
}

t_cmd	*create_cmd_node(void)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->arg = NULL;
	node->fdin = -1;
	node->fdout = -1;
	node->n_args = 0;
	node->next = NULL;
	return (node);
}

void	copy_arguments(t_cmd *cmd, char **new_args)
{
	int	i;

	i = 0;
	while (i < cmd->n_args)
	{
		new_args[i] = cmd->arg[i];
		i++;
	}
}

void	add_argument(t_cmd *cmd, const char *arg)
{
	char	**new_args;

	new_args = malloc(sizeof(char *) * (cmd->n_args + 2));
	if (!new_args)
	{
		perror("malloc failed");
		return ;
	}
	copy_arguments(cmd, new_args);
	new_args[cmd->n_args] = ft_strdup(arg);
	if (!new_args[cmd->n_args])
	{
		perror("ft_strdup failed");
		free(new_args);
		return ;
	}
	new_args[cmd->n_args + 1] = NULL;
	free(cmd->arg);
	cmd->arg = new_args;
	cmd->n_args++;
}

int	handle_redirection(t_cmd *cmd, t_token **token, t_env *env)
{
	int	status;

	status = 0;
	if (cmd == NULL || token == NULL || *token == NULL)
	{
		perror("Error: invalid pointer");
		return (1);
	}
	if ((*token)->type == IN || (*token)->type == OUT \
	|| (*token)->type == APPEND || (*token)->type == HEREDOC)
	{
		status = ft_innout(cmd, token, env);
		if (status != 0)
			return (status);
	}
	return (0);
}

int	fill_cmd_args(t_cmd *cmd, t_token **token, t_env *env)
{
	int	status;

	status = 0;
	while (*token && (*token)->type != PIPE)
	{
		if ((*token)->type == IN || (*token)->type == OUT \
		|| (*token)->type == APPEND || (*token)->type == HEREDOC)
		{
			status = handle_redirection(cmd, token, env);
			if (status != 0)
				break ;
		}
		else if ((*token)->type == WORD || \
		(*token)->type == QUOTE || (*token)->type == DQUOTE)
		{
			add_argument(cmd, (*token)->content);
			*token = (*token)->next;
		}
		else
			*token = (*token)->next;
	}
	return (status);
}

int	add_cmd_to_shell(t_cmd **cmd_list, t_token **token, t_env *env)
{
	t_cmd	*new_cmd;
	int		status;

	new_cmd = create_cmd_node();
	status = 0;
	if (!new_cmd)
		return (1);
	status = fill_cmd_args(new_cmd, token, env);
	if (status == 0)
		add_cmd_to_list(cmd_list, new_cmd);
	else
		free_cmd(&new_cmd);
	return (status);
}

void	token_to_cmd(t_shell *data)
{
	int		status;
	t_token	*token_ptr;

	status = 0;
	token_ptr = data->token;
	while (token_ptr)
	{
		if (token_ptr->type != PIPE)
		{
			status = add_cmd_to_shell(&data->cmd, &token_ptr, data->env);
			if (status != 0)
			{
				clear_structs(&token_ptr, &data->cmd);
				break ;
			}
		}
		else if (token_ptr->type == PIPE)
			token_ptr = token_ptr->next;
	}
}
