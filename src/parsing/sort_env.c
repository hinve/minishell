/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpino-mo <hpino-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:28:42 by mjeannin          #+#    #+#             */
/*   Updated: 2024/11/17 16:47:39 by hpino-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_env_len(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

void	swap_env_nodes(t_env *current, t_env *next)
{
	char	*tmp_key;
	char	*tmp_value;

	tmp_key = current->key;
	tmp_value = current->value;
	current->key = next->key;
	current->value = next->value;
	next->key = tmp_key;
	next->value = tmp_value;
}

int	compare_and_swap_nodes(t_env **head)
{
	t_env	*current;
	t_env	*next;
	int		swapped;
	int		i;

	current = *head;
	next = current->next;
	swapped = 0;
	i = 0;
	while (next)
	{
		if (ft_strcmp(current->key, next->key) > 0)
		{
			swap_env_nodes(current, next);
			swapped = 1;
		}
		current = next;
		next = next->next;
		i++;
	}
	return (swapped);
}

void	sort_env(t_env **env)
{
	int		env_len;
	int		ordered;
	t_env	*current;
	int		i;

	env_len = str_env_len(*env);
	ordered = 0;
	while (!ordered)
	{
		ordered = 1;
		current = *env;
		i = 0;
		while (i < env_len - 1)
		{
			if (compare_and_swap_nodes(&current))
				ordered = 0;
			current = current->next;
			i++;
		}
		env_len--;
	}
}

void	print_sorted_env(t_env *env)
{
	sort_env(&env);
	while (env)
	{
		printf("declare -x %s=%s\n", env->key, env->value);
		env = env->next;
	}
}
