/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:25:43 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/01 18:25:44 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_in(char *str_cmd, t_token **tok, int *i)
{
	if (str_cmd[*i + 1] == '<')
	{
		create_list(HEREDOC, tok, ft_strdup("<<"));
		*i += 2;
	}
	else
	{
		create_list(IN, tok, ft_strdup("<"));
		*i += 1;
	}
}

void	append_out(char *str_cmd, t_token **tok, int *i)
{
	if (str_cmd[*i + 1] == '>')
	{
		create_list(APPEND, tok, ft_strdup(">>"));
		*i += 2;
	}
	else
	{
		create_list(OUT, tok, ft_strdup(">"));
		*i += 1;
	}
}
