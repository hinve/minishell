/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpino-mo <hpino-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:48:46 by hpino-mo          #+#    #+#             */
/*   Updated: 2024/11/17 17:06:00 by hpino-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_type(t_token *aux)
{
	printf("%sType: %s", G, Y);
	if (aux->type == PIPE)
		printf("PIPE");
	else if (aux->type == IN)
		printf("IN");
	else if (aux->type == OUT)
		printf("OUT");
	else if (aux->type == APPEND)
		printf("APPEND");
	else if (aux->type == QUOTE)
		printf("QUOTE");
	else if (aux->type == DQUOTE)
		printf("DQUOTE");
	else if (aux->type == HEREDOC)
		printf("HEREDOC");
	else if (aux->type == WORD)
		printf("WORD");
	printf("%s\n", RST);
}

void	print_token(t_token *aux, int i)
{
	printf("%sNode: %d%s\n", RED, i, RST);
	printf("%sContent: %s%s%s\n", W, Y, aux->content, RST);
	print_token_type(aux);
}

void	print_lists(t_token *tok)
{
	t_token	*aux;
	int		i;

	i = 1;
	aux = tok;
	printf("%sLIST%s\n", C, RST);
	while (aux)
	{
		print_token(aux, i++);
		aux = aux->next;
	}
}
