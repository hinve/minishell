#include "minishell.h"

int	only_spaces(char *str_cmd)
{
	int	i;

	i = 0;
	while (str_cmd[i])
	{
		if (str_cmd[i] != ' ' && str_cmd[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
void	clear_env_structs(t_env **env, t_env **vars)
{
	t_env	*current_env;
	t_env	*next_env;

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
	data->var = NULL, data->envp = envp;
	data->status = 0;
}

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_ctrld(char *str_cmd)
{
	if (str_cmd == NULL)
	{
		printf("exit\n");
		exit(0);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	data;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	init_struct(&data, envp);
	print_banner();
	data.env = transform_env(envp);
	while (1)
	{
		if (quote_count(data.str_cmd) % 2 == 0)
			data.str_cmd = quote_union(data.str_cmd);
		data.str_cmd = readline(M "Mini" W "shell" G "--> " RST);
        handle_ctrld(data.str_cmd);
        add_history(data.str_cmd);
        if (!ft_strlen(data.str_cmd) || only_spaces(data.str_cmd) == 1)
        {
            free(data.str_cmd);
            continue;
        }
        lexer(data.str_cmd, &data.token);
        if (data.token != NULL && syntaxis_is_ok(&data.token) == 1)
        {
            expand_variables(&data);
            fill_struct(&data);
            execute_command(&data);
        }
        free(data.str_cmd);
        clear_structs(&data.token, &data.cmd);
	}
	return ((void)argc, (void)argv, 0);
}
