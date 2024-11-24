/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpino-mo <hpino-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:08:08 by mjeannin          #+#    #+#             */
/*   Updated: 2024/11/17 16:49:08 by hpino-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_fill_list(t_cmd **cmd, t_token **token, int argcs)
{
	t_cmd	*aux;

	if (!*cmd)
		*cmd = list_empty_fill(token, argcs);
	else
	{
		aux = list_empty_fill(token, argcs);
		add_back_fill(cmd, aux);
	}
}

int	count_args(t_token *token)
{
	int	argc;
	int	red;

	red = 0;
	argc = 0;
	while (token)
	{
		if (token->type == WORD)
			argc++;
		if (token->type == IN || token->type == OUT || token->type == APPEND
			|| token->type == HEREDOC)
			red++;
		token = token->next;
	}
	return (argc - red);
}

void	print_cmd_list(t_cmd *cmd)
{
	t_cmd	*aux;
	int		i;

	aux = cmd;
	while (aux)
	{
		i = 0;
		while (aux->arg[i])
		{
			printf("arg[%d]: %s\n", i, aux->arg[i]);
			i++;
		}
		printf("n_args: %d\n", aux->n_args);
		aux = aux->next;
	}
}

void	fill_struct(t_shell *data)
{
	int	argcs;

	argcs = count_args(data->token);

	while (data->token)
	{
		if (data->token->type != PIPE)
			create_fill_list(&data->cmd, &data->token, argcs);
		else if (data->token->type == PIPE)
		{
			data->token = data->token->next;
		}
	}
}

void fill_struct_new(t_shell **data)
{
    int i;

    i = 0;

    (*data)->newcmd = malloc(sizeof(t_newcmd));
    if (!(*data)->newcmd)
    {
        printf("Error allocating memory\n");
        exit(1);
    }

    (*data)->newcmd->command = (*data)->str_cmd;
    (*data)->newcmd->countPipes = 0; // Inicializa countPipes a 0

    while((*data)->newcmd->command[i])
    {
        if((*data)->newcmd->command[i] == '|')
        {
            (*data)->newcmd->countPipes++;
        }
        i++;
    }
}
