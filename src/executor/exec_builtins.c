#include "minishell.h"

int	execute_builtin(t_shell *data)
{
	if (data->cmd->n_args == 0)
        return (0);
	if (ft_strcmp(data->cmd->arg[0], "echo") == 0)
		return (ft_echo(data->cmd), 1);
    else if(ft_strcmp(data->cmd->arg[0], "pwd") == 0)
		return (ft_pwd(), 1);
	else if(ft_strcmp(data->cmd->arg[0], "cd") == 0)
		return (ft_cd(data), 1);
	else if(ft_strcmp(data->cmd->arg[0], "export") == 0)
		return (ft_export(data), 1);
	else if(ft_strcmp(data->cmd->arg[0], "unset") == 0)
		return (ft_unset(data), 1);
	else if(ft_strcmp(data->cmd->arg[0], "env") == 0)
		return (ft_env(data->env), 1);
	else if(ft_strcmp(data->cmd->arg[0], "exit") == 0)
		return (ft_exit(data->cmd), 1);
	else
		return (0);
}
