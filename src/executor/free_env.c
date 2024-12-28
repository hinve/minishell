/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:38:24 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/27 14:38:58 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		if (temp->key)
		{
			free(temp->key);
			temp->key = NULL;
		}
		if (temp->value)
		{
			free(temp->value);
			temp->value = NULL;
		}
		free(temp);
		temp = NULL;
	}
}

void	free_env_node(t_env **node)
{
	if (*node)
	{
		if ((*node)->key)
		{
			free((*node)->key);
			(*node)->key = NULL;
		}
		if ((*node)->value)
		{
			free((*node)->value);
			(*node)->value = NULL;
		}
		free(*node);
		*node = NULL;
	}
}
