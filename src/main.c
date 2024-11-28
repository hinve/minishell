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

int main(int argc, char **argv, char **envp)
{
    t_shell data;

    init(&data, envp);
    while (1)
    {
        data.str_cmd = readline(M "Mini" W "shell" G "--> " RST);
        if (!data.str_cmd)
            break ;
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
        data.cmd_count = 0;
        data.str_cmd = NULL;
    }
    free_all(&data);
    return ((void)argc, (void)argv, 0);
}
