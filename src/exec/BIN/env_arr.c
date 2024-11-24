/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:05:05 by matta             #+#    #+#             */
/*   Updated: 2024/11/21 16:26:23 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_array(char **env_array, int count)
{
	while (count > 0)
	{
		free(env_array[--count]);
	}
	free(env_array);
}

char	*create_env_entry(const char *key, const char *value)
{
	size_t	len;
	char	*entry;

	len = strlen(key) + strlen(value) + 2;
	entry = malloc(len);
	if (entry)
	{
		ft_strcpy(entry, key);
		ft_strcat(entry, "=");
		ft_strcat(entry, value);
	}
	return (entry);
}

int	populate_env_array(t_env *env, char **env_array)
{
	int	i;

	i = 0;
	while (env)
	{
		env_array[i] = create_env_entry(env->key, env->value);
		if (!env_array[i])
		{
			free_env_array(env_array, i);
			return (0);
		}
		i++;
		env = env->next;
	}
	env_array[i] = NULL;
	return (1);
}

char	**allocate_env_array(int count)
{
	char	**env_array;

	env_array = malloc((count + 1) * sizeof(char *));
	if (!env_array)
	{
		perror("malloc");
		return (NULL);
	}
	return (env_array);
}

char	**convert_env_to_array(t_env *env)
{
	int		count;
	t_env	*temp;
	char	**env_array;

	count = 0;
	env_array = allocate_env_array(count);
	count = 0;
	temp = env;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	if (!env_array)
		return (NULL);
	if (!populate_env_array(env, env_array))
	{
		free(env_array);
		return (NULL);
	}
	return (env_array);
}
