/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:34:23 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/27 10:35:50 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add(t_env **head, char *key, char *value)
{
	t_env	*new_node;
	t_env	*temp;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (free(key), free(value));
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
	}
}

void	remove_head(t_env **head)
{
	t_env	*temp;

	temp = *head;
	*head = (*head)->next;
	free_env_node(&temp);
}

void	remove_node(t_env **head, t_env *prev, t_env *current)
{
	if (prev == NULL)
	{
		*head = current->next;
	}
	else
	{
		prev->next = current->next;
	}
	free_env_node(&current);
}

void	pop(t_env **head, char *key)
{
	t_env	*prev;
	t_env	*current;

	prev = NULL;
	current = *head;
	while (current != NULL && ft_strcmp(current->key, key) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (current == NULL)
		return ;
	remove_node(head, prev, current);
}

t_cmd	*get_last_cmd(t_cmd *cmd)
{
	t_cmd	*aux;

	aux = cmd;
	while (aux->next)
		aux = aux->next;
	return (aux);
}
