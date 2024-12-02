/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:19:43 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/01 18:19:44 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_stuff(int *i, char *str_cmd)
{
	int	quote_count;

	quote_count = 0;
	while (str_cmd[*i])
	{
		*i += 1;
		if (str_cmd[*i] == '\'')
			return (quote_count);
		else if (str_cmd[*i + 1] == '\0')
			return (-1);
		quote_count++;
	}
	return (0);
}

int	dquote_stuff(int *i, char *str_cmd)
{
	int	quote_count;

	quote_count = 0;
	while (str_cmd[*i])
	{
		*i += 1;
		if (str_cmd[*i] == '"')
			return (quote_count);
		else if (str_cmd[*i + 1] == '\0')
			return (-1);
		quote_count++;
	}
	return (0);
}
