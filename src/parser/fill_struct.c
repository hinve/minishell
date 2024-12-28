/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:28:25 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/28 13:08:11 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_struct(t_shell *data)
{
	printf("Filling shell commands...\n");
	while (data->token)
	{
		if (data->token->type != PIPE)
		{
			printf("Adding command to shell...\n");
			add_cmd_to_shell(&data->cmd, &data->token, data->env);
		}
		else if (data->token->type == PIPE)
		{
			printf("Found PIPE, moving to next token...\n");
			data->token = data->token->next;
		}
	}
}
