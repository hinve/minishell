/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:43:31 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/02 14:43:32 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tokens(t_token *token)
{
    while (token)
    {
        printf("Token: %s, Type: %d\n", token->content, token->type);
        token = token->next;
    }
}

void is_line_is_empty(char *str)
{
    free(str);
    str = readline(M "Mini" W "shell" G "--> " RST);
}

void    handle_empty_or_whitespace_commands(char **str_cmd)
{
    if (!ft_strlen(*str_cmd) || only_spaces(*str_cmd) == 1)
    {
        free(*str_cmd);
        *str_cmd = readline(M "Mini" W "shell" G "--> " RST);
    }
}

static void	minishell(t_shell *data)
{
	if (data->token != NULL && syntaxis_is_ok(&data->token) == 1)
	{
		expand_variables(&data->token, data->env, data);
		token_to_cmd(data);
		if (data->cmd != NULL)
		{
			executor(data);
			clear_structs(&data->token, &data->cmd);
		}
	}
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

int main(int argc, char **argv, char **envp)
{
    t_shell data;

    init(&data, envp);
    while (1)
    {
        data.str_cmd = readline(M "Mini" W "shell" G "--> " RST);
        if (!data.str_cmd)
        {
            ft_printf("\nexit\n");
            break ;
        }
        add_history(data.str_cmd);
        if (!ft_strlen(data.str_cmd) || only_spaces(data.str_cmd) == 1)
        {
            free(data.str_cmd);
            data.str_cmd = readline(M "Mini" W "shell" G "--> " RST);
            continue;
        }
        lexer(data.str_cmd, &data.token);
        minishell(&data);
        free(data.str_cmd);
        clear_structs_main(&data.token, &data.cmd);
        data.cmd_count = 0;
        data.str_cmd = NULL;
    }
    free_all(&data);
    return ((void)argc, (void)argv, 0);
}
