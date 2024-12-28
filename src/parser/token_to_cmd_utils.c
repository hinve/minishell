/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:18:30 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/28 13:20:07 by mjeannin         ###   ########.fr       */
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

void	add_argument(t_cmd *cmd, char *token_content)
{
	char	**new_arg;
	int		i;

	i = 0;
	new_arg = (char **)malloc(sizeof(char *) * (cmd->n_args + 2));
	if (!new_arg)
		perror("Error: allocating memory");
	while (i < cmd->n_args)
	{
		new_arg[i] = cmd->arg[i];
		i++;
	}
	new_arg[cmd->n_args] = ft_strdup(token_content);
	new_arg[cmd->n_args + 1] = NULL;
	cmd->arg = new_arg;
	cmd->n_args++;
}
