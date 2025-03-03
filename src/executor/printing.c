/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:05:17 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/27 10:33:34 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_env *head)
{
	t_env	*current;

	current = head;
	while (current)
	{
		if (current->key && current->value)
			printf("%s=%s\n", current->key, current->value);
		else if (current->key)
			printf("%s=\n", current->key);
		else if (current->value)
			printf("=%s\n", current->value);
		current = current->next;
	}
}

void	print_key(t_env *head)
{
	t_env	*temp;

	temp = head;
	while (temp != NULL)
	{
		printf("%s\n", temp->key);
		temp = temp->next;
	}
}

char	*print_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(env->key) + 1) == 0)
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

void	print_argu(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		printf("Arg[%d]: %s\n", i, args[i]);
		i++;
	}
}
