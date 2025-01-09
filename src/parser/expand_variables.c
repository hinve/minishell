/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:28:42 by mjeannin          #+#    #+#             */
/*   Updated: 2025/01/07 14:32:01 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_variables(t_token **token, t_shell *data)
{
	t_token	*aux;
	char	*new_content;

	aux = *token;
	while (aux)
	{
		if (aux->type == HEREDOC)
		{
			aux = aux->next;
		}
		else
		{
			if (is_there_a_dollar(aux->content) && \
				(aux->type == DQUOTE || aux->type == WORD))
			{
				new_content = replace_dollar(aux->content, data);
				free(aux->content);
				aux->content = ft_strdup(new_content);
				free (new_content);
			}
			aux = aux->next;
		}
	}
}
