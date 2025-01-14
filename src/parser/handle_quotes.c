/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:24:03 by mjeannin          #+#    #+#             */
/*   Updated: 2025/01/14 14:44:42 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	aux = malloc(sizeof(char) * (ft_strlen(str) + 1));
	i = 0;
	j = 0;
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

int	quote_count(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			count++;
		}
		i++;
	}
	return (count);
}
