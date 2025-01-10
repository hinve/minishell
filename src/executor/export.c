/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:51:24 by mjeannin          #+#    #+#             */
/*   Updated: 2025/01/10 14:08:15 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	unvalid_format(char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (1);
		if (str[i] == '=')
		{
			if (sign == 1 || !ft_isalnum(str[i + 1]))
				return (1);
			sign = 1;
		}
		i++;
	}
	return (0);
}

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

static void	update_or_add_node(t_env **list, char *key, char *value)
{
	t_env	*node;

	node = find_node(*list, key);
	if (node)
	{
		free(node->value);
		node->value = ft_strdup(value);
	}
	else
	{
		add(list, ft_strdup(key), ft_strdup(value));
	}
}

static void	handle_vars(t_shell *data)
{
    char	*key;
    char	*value;

    if (ft_strchr(data->cmd->arg[1], '='))
    {
        get_key_value(data->cmd->arg[1], &key, &value);
    }
    else
    {
        key = ft_strdup(data->cmd->arg[1]);
        value = ft_strdup("");
    }
    update_or_add_node(&data->export, key, value);
    update_or_add_node(&data->env, key, value);
	printf("input %d : %s %s\n", 1, key, value);
    free(key);
    free(value);
}

void	ft_export(t_shell *data)
{
	t_env	*export;
	t_env	*temp;

	if (!unvalid_format(data->cmd->arg[1]))
		return ;
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
