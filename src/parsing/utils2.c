/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpino-mo <hpino-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:06:54 by mjeannin          #+#    #+#             */
/*   Updated: 2024/11/17 16:40:38 by hpino-mo         ###   ########.fr       */
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

char	*own_get_env(char *key)
{
	extern char	**environ;
	int			i;
	int			j;
	char		*value;
	char		*env_key;

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

void	handle_double_quotes(char *str, char *aux, int *i, int *j)
{
	(*i)++;
	while (str[*i] != '"' && str[*i] != '\0')
		aux[(*j)++] = str[(*i)++];
	if (str[*i] == '"')
		(*i)++;
}

void	handle_single_quotes(char *str, char *aux, int *i, int *j)
{
	aux[(*j)++] = str[(*i)++];
	while (str[*i] != '\'' && str[*i] != '\0')
		aux[(*j)++] = str[(*i)++];
	if (str[*i] == '\'')
		aux[(*j)++] = str[(*i)++];
}

char	*quote_union(char *str)
{
	char	*aux;
	int		i;
	int		j;

	i = 0;
	j = 0;
	aux = malloc(sizeof(char) * (strlen(str) + 1));
	if (!aux)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"')
			handle_double_quotes(str, aux, &i, &j);
		else if (str[i] == '\'')
			handle_single_quotes(str, aux, &i, &j);
		else
			aux[j++] = str[i++];
	}
	aux[j] = '\0';
	return (aux);
}
