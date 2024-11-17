/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpino-mo <hpino-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:01:10 by hpino-mo          #+#    #+#             */
/*   Updated: 2024/11/17 17:01:11 by hpino-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_utils(char *line, char *temp, int *i, int *temp_len)
{
	char	*aux;
	int		j;
	char	*new_temp;
	char	*env_value;

	aux = (char *)malloc(256 * sizeof(char));
	j = 0;
	(*i)++;
	while (line[*i] && ft_isalnum(line[*i]))
		aux[j++] = line[(*i)++];
	aux[j] = '\0';
	env_value = own_get_env(aux);
	if (!env_value)
		env_value = "";
	new_temp = ft_strjoin(temp, env_value);
	*temp_len += ft_strlen(env_value);
	free(aux);
	free(temp);
	return (new_temp);
}

char	*expand_heredoc(char *line)
{
	char	*temp;
	int		i;
	int		temp_len;

	temp = ft_strdup("");
	i = 0;
	temp_len = 0;
	while (line[i])
	{
		if (line[i] == '$')
			temp = expand_utils(line, temp, &i, &temp_len);
		else
			temp[temp_len++] = line[i++];
	}
	temp[temp_len] = '\0';
	return (temp);
}
