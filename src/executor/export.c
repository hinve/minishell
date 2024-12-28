/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:51:24 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/28 13:31:38 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_node(t_env *head, char *key)
{
	if (!head || !key)
		return (NULL);
	while (head)
	{
		if (ft_strcmp(head->key, key) == 0)
			return (head);
		head = head->next;
	}
	return (NULL);
}

static void	update_or_add(t_env **list, char *key, char *value)
{
	t_env	*node;

	node = find_node(*list, key);
	if (node)
	{
		free(node->value);
		node->value = value;
		free(key);
	}
	else
	{
		add(list, key, value);
	}
}

static void	handle_vars(t_shell *data)
{
	char	*key;
	char	*value;
	int		i;

	i = 1;
	while (i < data->cmd->n_args)
	{
		get_key_value(data->cmd->arg[i++], &key, &value);
		update_or_add(&data->export, key, value);
		if (value)
		{
			update_or_add(&data->env, strdup(key), strdup(value));
		}
		else
		{
			free(key);
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
