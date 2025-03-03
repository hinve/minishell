/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:22:54 by mjeannin          #+#    #+#             */
/*   Updated: 2025/01/14 14:57:58 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer(char *str_cmd, t_token **tok)
{
	int	i;

	i = 0;
	while (str_cmd[i])
	{
		if (str_cmd[i] == '|')
			set_token(PIPE, str_cmd, tok, &i);
		else if (str_cmd[i] == '<')
			set_token(IN, str_cmd, tok, &i);
		else if (str_cmd[i] == '>')
			set_token(OUT, str_cmd, tok, &i);
		else if (str_cmd[i] == '\'')
			set_token(QUOTE, str_cmd, tok, &i);
		else if (str_cmd[i] == '"')
			set_token(DQUOTE, str_cmd, tok, &i);
		else if (str_cmd[i] != '|' && str_cmd[i] != '<' && str_cmd[i] != '>'
			&& str_cmd[i] != '\'' && str_cmd[i] != '"' && str_cmd[i] != ' ')
			set_token(WORD, str_cmd, tok, &i);
		else
			i++;
	}
}
