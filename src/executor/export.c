/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:42:55 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/04 17:37:26 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_vars(t_shell *data)
{
	char	*key;
	char	*value;
	int		i;

	i = 1;
	while (i < data->cmd->n_args)
	{
		get_key_value(data->cmd->arg[i++], &key, &value);
		pop(&data->export, key);
		add(&data->export, key, value);
		if (value)
		{
			pop(&data->env, key);
			add(&data->env, key, value);
		}
	}
}

void	ft_export(t_shell *data)
{
	t_env	*export;
	t_env	*temp;

	handle_vars(data);
	printf("n_args : %d\narg1 %s\narg 2 : %s\n", data->cmd->n_args, data->cmd->arg[1], data->cmd->arg[2]);
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
