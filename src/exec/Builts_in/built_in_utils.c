#include "minishell.h"

int		exec_built_in(t_shell *data)
{
    int stat;

    stat = 0;
    if (!ft_strcmp(data->cmd->arg[0], "unset"))
        stat = ft_unset(data);
    else if (!ft_strcmp(data->cmd->arg[0], "pwd"))
		stat = ft_pwd(data);
    else if (!ft_strcmp(data->cmd->arg[0], "env"))
        stat = ft_env(data);
    else if (!ft_strcmp(data->cmd->arg[0], "exit"))
		ft_exit(data);
    else if (!ft_strcmp(data->cmd->arg[0], "echo"))
		stat = ft_echo(data);
	else if (!ft_strcmp(data->cmd->arg[0], "export"))
        stat = ft_export(data);
    else if(!ft_strcmp(data->cmd->arg[0], "cd"))
        stat = ft_cd(data);
    return(status(data, stat));
}

int is_built_in(t_shell *data)
{
    if (ft_strcmp(data->cmd->arg[0], "pwd") == 0 || 
        ft_strcmp(data->cmd->arg[0], "env") == 0 || 
        ft_strcmp(data->cmd->arg[0], "echo") == 0 || 
        ft_strcmp(data->cmd->arg[0], "export") == 0 || 
        ft_strcmp(data->cmd->arg[0], "man") == 0 || 
        ft_strcmp(data->cmd->arg[0], "cd") == 0 || 
        ft_strcmp(data->cmd->arg[0], "exit") == 0 ||
        ft_strcmp(data->cmd->arg[0], "unset") == 0)
 
    {
        return (1);
    }
    return (status(data,0));
}