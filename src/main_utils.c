/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpino-mo <hpino-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:47:33 by hpino-mo          #+#    #+#             */
/*   Updated: 2025/01/14 12:48:02 by hpino-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_user_input(t_shell *data)
{
	data->str_cmd = readline(M "Mini" W "shell" G "--> " RST);
	add_history(data->str_cmd);
	if (!data->str_cmd)
	{
		ft_printf("\nexit\n");
		free_all(data);
		exit(0);
	}
	remove_quotes_and_spaces(&data->str_cmd);
	if (quote_count(data->str_cmd) % 2 == 0)
		data->str_cmd = quote_union(data->str_cmd);
}

void	handle_empty_or_whitespace(t_shell *data)
{
	if (!ft_strlen(data->str_cmd) || only_spaces(data->str_cmd) == 1)
	{
		free(data->str_cmd);
		data->str_cmd = readline(M "Mini" W "shell" G "--> " RST);
	}
}

void	minishell(t_shell *data)
{
	if (data->token != NULL && syntaxis_is_ok(&data->token) == 1)
	{
		expand_variables(&data->token, data);
		token_to_cmd(data);
		if (data->cmd != NULL)
		{
			executor(data);
			clear_structs(&data->token, &data->cmd);
		}
	}
}

void	process_commands(t_shell *data)
{
	lexer(data->str_cmd, &data->token);
	minishell(data);
	free(data->str_cmd);
	clear_structs_main(&data->token, &data->cmd);
	data->cmd_count = 0;
	data->str_cmd = NULL;
}

void	clear_structs_main(t_token **token, t_cmd **cmd)
{
	t_token	*current;
	t_cmd	*current_cmd;
	t_cmd	*next_cmd;
	t_token	*next;

	current = *token;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	current_cmd = *cmd;
	while (current_cmd != NULL)
	{
		if (current_cmd->fdin != -1)
			close(current_cmd->fdin);
		if (current_cmd->fdout != -1)
			close(current_cmd->fdout);
		next_cmd = current_cmd->next;
		free(current_cmd);
		current_cmd = next_cmd;
	}
	*cmd = NULL;
	*token = NULL;
}
