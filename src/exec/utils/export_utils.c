/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:57:08 by mjeannin          #+#    #+#             */
/*   Updated: 2024/11/21 15:26:47 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_put_var(t_env **env, const char *arg)
{
	char	*key;
	char	*value;
	t_env	*existing_var;

	split_key_value(arg, &key, &value);
	existing_var = find_env_var(*env, key);
	if (existing_var != NULL)
		update_existing_var(existing_var, value, key);
	else
		add_new_var(env, key, value);
}

t_env	*find_env_var(t_env *env, const char *key)
{
	while (env)
	{
		if (ft_strcmp(env->key, (char *)key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	free_env_list(t_env *env)
{
	t_env	*current;

	while (env)
	{
		current = env;
		env = env->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
	}
}

void	print_env_list(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}

t_env	*get_min_env(t_env **env)
{
	t_env	*min;
	t_env	**min_prev;
	t_env	*current;
	t_env	**prev;

	min = *env;
	min_prev = env;
	current = (*env)->next;
	prev = &(*env)->next;
	while (current)
	{
		if (ft_strcmp(current->key, min->key) < 0)
		{
			min = current;
			min_prev = prev;
		}
		prev = &current->next;
		current = current->next;
	}
	*min_prev = min->next;
	return (min);
}
