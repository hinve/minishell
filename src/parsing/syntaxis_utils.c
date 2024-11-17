/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxis_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpino-mo <hpino-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:40:13 by hpino-mo          #+#    #+#             */
/*   Updated: 2024/11/17 16:42:06 by hpino-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_in_out_error(t_token *aux)
{
	if (aux->next == NULL)
	{
		printf("minishell: syntax error near unexpected token 'newline'\n");
		return (1);
	}
	return (0);
}

int	check_in_out_token_type(t_token *aux)
{
	if ((aux->type == IN && aux->next->type != WORD) || (aux->type == HEREDOC
			&& aux->next->type != WORD))
	{
		printf("minishell: syntax error near unexpected token '<'\n");
		return (1);
	}
	else if ((aux->type == OUT && aux->next->type != WORD)
		|| (aux->type == APPEND && aux->next->type != WORD))
	{
		printf("minishell: syntax error near unexpected token '>'\n");
		return (1);
	}
	return (0);
}

int	in_out_parser(t_token **tok)
{
	t_token	*aux;

	aux = *tok;
	while (aux && aux->type != IN && aux->type != OUT && aux->type != APPEND
		&& aux->type != HEREDOC)
		aux = aux->next;
	if (aux && (aux->type == IN || aux->type == OUT || aux->type == APPEND
			|| aux->type == HEREDOC))
	{
		if (check_in_out_error(aux))
			return (1);
		if (check_in_out_token_type(aux))
			return (1);
	}
	return (0);
}

int	check_first_pipe(t_token *aux)
{
	if (aux && aux->type == PIPE)
	{
		printf("Error: syntax error near unexpected token '|'\n");
		return (1);
	}
	return (0);
}

int	check_consecutive_pipes(t_token *aux)
{
	while (aux->next)
	{
		if (aux->type == PIPE && aux->next->type == PIPE)
		{
			printf("Error: syntax error near unexpected token '||'\n");
			return (1);
		}
		aux = aux->next;
	}
	return (0);
}
