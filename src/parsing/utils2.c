/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:06:54 by mjeannin          #+#    #+#             */
/*   Updated: 2024/10/02 14:07:58 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(t_env *env, const char *key)
{
	if (env == NULL || key == NULL)
		perror("Error: null arguments");
	while (env != NULL && env->next != NULL)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key) + 1))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char *own_get_env(char *key)
{
	extern char **environ;
	int i;
	int j;
	char *value;
	char *env_key;

	i = 0;
	while (environ[i])
	{
		j = 0;
		while (environ[i][j] != '=')
			j++;
		env_key = ft_substr(environ[i], 0, j);
		if (!ft_strcmp(env_key, key))
		{
			value = ft_strdup(&environ[i][j + 1]);
			free(env_key);
			return (value);
		}
		free(env_key);
		i++;
	}
	return (NULL);
}

/* char *quote_union(char *str)
{
	int i;
	int q_count;
	int dq_count;

	dq_count = 0;
	q_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			q_count++;
		else if (str[i] == '"')
			dq_count++;
		i++;
	}
	if (q_count % 2 != 0 || dq_count % 2 != 0)
		return (NULL);
	else
	{
		printf("quote union\n");
	}
	return (str);
} */
