/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpino-mo <hpino-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:25:50 by mjeannin          #+#    #+#             */
/*   Updated: 2024/11/17 16:42:08 by hpino-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_last_pipe(t_token *aux)
{
	if (aux && aux->type == PIPE)
	{
		printf("Error: syntax error near unexpected token '|'\n");
		return (1);
	}
	return (0);
}

int	pipe_parser(t_token *tok)
{
	t_token	*aux;

	aux = tok;
	if (check_first_pipe(aux))
		return (1);
	if (check_consecutive_pipes(aux))
		return (1);
	if (check_last_pipe(aux))
		return (1);
	return (0);
}

int	is_special_line(t_token *tok, const char *content)
{
	return (ft_strncmp(tok->content, content, strlen(content)) == 0
		&& tok->next == NULL);
}

int	is_new_line(t_token *tok)
{
	return (is_special_line(tok, "\\n") || is_special_line(tok, "!")
		|| is_special_line(tok, ":"));
}

int	syntaxis_is_ok(t_token **token)
{
	if (is_new_line(*token))
		return (0);
	else if (pipe_parser(*token))
		return (0);
	else if (in_out_parser(token))
		return (0);
	return (1);
}
