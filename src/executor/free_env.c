/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:40:35 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/04 16:22:38 by mjeannin         ###   ########.fr       */
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
	}
}

void free_env_node(t_env **node)
{
    if (node && *node)
    {
        if ((*node)->key)
        {
            free((*node)->key);
            (*node)->key = NULL; // Set to NULL to avoid dangling pointer
        }
        if ((*node)->value)
        {
            free((*node)->value);
            (*node)->value = NULL; // Set to NULL to avoid dangling pointer
        }
        free(*node);
        *node = NULL; // Set to NULL to avoid dangling pointer
    }
}
