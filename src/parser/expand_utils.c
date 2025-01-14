/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpino-mo <hpino-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:32:22 by mjeannin          #+#    #+#             */
/*   Updated: 2025/01/14 12:38:28 by hpino-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value2(const char *var, t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strncmp(current->key, var, ft_strlen(var)) == 0
			&& current->key[ft_strlen(var)] == '\0')
		{
			return (current->value);
		}
		current = current->next;
	}
	return ("");
}

char	*get_env_var(char *line, int *i, t_env *env)
{
	int		start;
	char	*var_name;
	char	*value;

	start = *i + 1;
	if (ft_strcmp(line, "") == 0)
		return ("");
	(*i)++;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	var_name = ft_substr(line, start, *i - start);
	value = get_env_value2(var_name, env);
	free(var_name);
	if (value)
		return (value);
	else
		return ("");
}

char	*process_variable(char *line, int *i, t_env *env, char *temp)
{
	char	*value;

	value = get_env_var(line, i, env);
	printf("Found variable: %s\n", value);
	temp = ft_strjoin(temp, value);
	return (temp);
}

char	*process_character(char *line, int *i, char *temp)
{
	char	c[2];

	c[0] = line[*i];
	c[1] = '\0';
	temp = ft_strjoin(temp, c);
	(*i)++;
	return (temp);
}

char	*expand_heredoc(char *line, t_env *env)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_strdup("");
	if (!temp)
		return (NULL);
	while (line && line[i])
	{
		printf("Processing character: %c\n", line[i]);
		if (line[i] == '$' && ft_isalpha(line[i + 1]))
			temp = process_variable(line, &i, env, temp);
		else
			temp = process_character(line, &i, temp);
	}
	return (temp);
}
