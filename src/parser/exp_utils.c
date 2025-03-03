/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:33:37 by mjeannin          #+#    #+#             */
/*   Updated: 2025/02/06 17:26:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(const char *var, t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strncmp(current->key, var, ft_strlen(var)) == 0
			&& current->key[ft_strlen(var)] == '\0')
			return (current->value);
		current = current->next;
	}
	return ("");
}

static char	*extract_var_name(const char *str, int *i)
{
	int		k;
	char	*var_name;

	k = 0;
	var_name = malloc(sizeof(char) * 256);
	if (!var_name)
		return (NULL);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		var_name[k++] = str[(*i)++];
	var_name[k] = '\0';
	return (var_name);
}

static int	append_env_value(char *result, int j, char *env_value)
{
	int	l;

	l = -1;
	while (env_value && env_value[++l])
		result[j++] = env_value[l];
	return (j);
}

char	*process_dollar(char *str, int *i, int *j, t_shell *data)
{
	char	*var_name;
	char	*value;

	(*i)++;
	var_name = extract_var_name(str, i);
	value = get_env_value(var_name, data->env);
	*j = append_env_value(data->result, *j, value);
	free(var_name);
	return (data->result);
}

char	*replace_dollar(char *str, t_shell *data)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	data->result = malloc(sizeof(char) * 1024);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && \
		(ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
			data->result = process_dollar(str, &i, &j, data);
		else if (str[i + 1] == '?' && str[i] == '$')
		{
			i += 2;
			value = ft_itoa(data->status);
			j = append_env_value(data->result, j, value);
			free(value);
		}
		else
			data->result[j++] = str[i++];
	}
	data->result[j] = '\0';
	return (data->result);
}
