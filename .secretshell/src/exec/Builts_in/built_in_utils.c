#include "minishell.h"

int		exec_built_in(t_shell *data)
{
    printf("ping exec reached\n");
    if (!ft_strcmp(data->cmd->arg[0], "pwd"))
		data->status = ft_pwd();
    else if (!ft_strcmp(data->cmd->arg[0], "env"))
        data->status = ft_env(data);
    else if (!ft_strcmp(data->cmd->arg[0], "exit"))
		ft_exit(data);
    else if (!ft_strcmp(data->cmd->arg[0], "echo"))
		data->status = ft_echo(data);
	else if (!ft_strcmp(data->cmd->arg[0], "export"))
        data->status = ft_export(data);
    else if(!ft_strcmp(data->cmd->arg[0], "man"))
        data->status = ft_man(data);
    else if(ft_strcmp(data->cmd->arg[0], "cd") == 0)
        data->status = ft_cd(data);
    else if(ft_strcmp((char *)data->cmd->arg[0], "unset") == 0)
        data->status = ft_unset(data);
    return(0);
}

int is_built_in(t_shell *data)
{
    if (ft_strcmp(data->cmd->arg[0], "pwd") == 0 || 
        ft_strcmp(data->cmd->arg[0], "env") == 0 || 
        ft_strcmp(data->cmd->arg[0], "echo") == 0 || 
        ft_strcmp(data->cmd->arg[0], "export") == 0 || 
        ft_strcmp(data->cmd->arg[0], "man") == 0 || 
        ft_strcmp(data->cmd->arg[0], "cd") == 0 || 
        ft_strcmp(data->cmd->arg[0], "exit") == 0)
    {
        return (1);
    }
    return (0);
}