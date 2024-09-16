#include "minishell.h"

int	only_spaces(char *str_cmd)
{
	int	i;

	i = 0;
	while (str_cmd[i])
	{
		if (str_cmd[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
void clear_env_structs(t_env **env, t_env **vars)
{
    t_env *current_env;
    t_env *next_env;

    // Clear environment variables
    current_env = *env;
    while (current_env != NULL)
    {
        next_env = current_env->next;
        free(current_env->key);
        free(current_env->value);
        free(current_env);
        current_env = next_env;
    }
    *env = NULL;

    // Clear additional variables
    current_env = *vars;
    while (current_env != NULL)
    {
        next_env = current_env->next;
        free(current_env->key);
        free(current_env->value);
        free(current_env);
        current_env = next_env;
    }
    *vars = NULL;
}

void	clear_structs(t_token **token, t_cmd **cmd)
{
	t_token	*current;
	t_cmd	*current_cmd;
	t_cmd	*next_cmd;
	t_token	*next;

	current = *token;
	current_cmd = *cmd;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
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

void	init_struct(t_shell *data, char **envp)
{
	data->token = NULL;
	data->cmd = NULL;
	data->env = NULL;
	data->var = NULL,
	data->envp = envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	data;

	(void)argc;
	(void)argv;
	init_struct(&data, envp);
	print_banner();
	data.str_cmd = readline(M "Mini" W "shell" G "--> " RST);
	data.env = transform_env(envp);
	while (data.str_cmd)
	{
		add_history(data.str_cmd);
		if (!ft_strlen(data.str_cmd) || only_spaces(data.str_cmd) == 1)
			data.str_cmd = readline(M "Mini" W "shell" G "--> " RST);
		lexer(data.str_cmd, &data.token);
		if (data.token != NULL && syntaxis_is_ok(&data.token) == 1)
		{
			expand_variables(&data.token, data.env);
			fill_struct(&data);
			execute_command(&data);
		}
		free(data.str_cmd);
		clear_structs(&data.token, &data.cmd);
		clear_env_structs(&data.env, &data.var);
		data.str_cmd = readline(M "Mini" W "shell" G "--> " RST);
	}
}
