/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:51:24 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/27 10:54:09 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_node(t_env *head, char *key)
{
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

static void	handle_vars(t_shell *data)
{
	char	*key;
	char	*value;
	int		i;
	t_env	*node;

	i = 1;
	while (i < data->cmd->n_args)
	{
		get_key_value(data->cmd->arg[i++], &key, &value);
		node = find_node(data->export, key);
		if (node)
		{
			free(node->value);
			node->value = value;
			free(key);
		}
		else
		{
			add(&data->export, key, value);
		}
		if (value)
		{
			node = find_node(data->env, key);
			if (node)
			{
				free(node->value);
				node->value = value;
			}
			else
			{
				add(&data->env, key, value);
			}
		}
	}
}

void	ft_export(t_shell *data)
{
	t_env	*export;
	t_env	*temp;

	handle_vars(data);
	if (data->cmd->n_args > 1)
		return ;
	export = data->export;
	while (export->key != NULL && export->next != NULL)
	{
		temp = export;
		while (temp->key && temp->next)
		{
			if (ft_strncmp(temp->key, temp->next->key, \
				ft_strlen(temp->key) + 1) > 0)
			{
				ft_swap(&temp->key, &temp->next->key);
				ft_swap(&temp->value, &temp->next->value);
			}
			temp = temp->next;
		}
		export = export->next;
	}
	print_list(data->export);
}
