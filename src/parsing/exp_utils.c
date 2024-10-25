/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpino-mo <hpino-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:08:47 by mjeannin          #+#    #+#             */
/*   Updated: 2024/10/25 13:38:30 by hpino-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_there_a_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' || str[i] == '-' || str[i] == '~')
			return (1);
		i++;
	}
	return (0);
}

char	*get_env_content(char *key, t_env *env)
{
	t_env	*current;

	current = env;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*get_var_value(char *key, t_env *var)
{
	t_env	*current;

	current = var;
	while (current != NULL)
	{
		if (strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*replace_dollar(char *line, t_shell *data)
{
	char	*key;
	char	*value;

	if (line[0] != '$')
		return (ft_strdup(line));
	else if (line[0] == '$' && line[1] == '?' && line[2] == '\0')
		return (ft_itoa(data->status));
	key = line + 1;
	value = get_env_content(key, data->env);
	if (value == NULL)
		value = get_var_value(key, data->var);
	if (value != NULL)
		return (ft_strdup(value));
	return (ft_strdup(""));
}
