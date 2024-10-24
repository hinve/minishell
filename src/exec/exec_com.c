
#include "minishell.h"

int		exec_builts_in(t_shell *data)
{

	int		result;

	result = 0;

    if (!ft_strcmp(data->cmd->arg[0], "pwd"))
		result = ft_pwd();
    else if (!ft_strcmp(data->cmd->arg[0], "env"))
        data->status = ft_env(data);
    else if (!ft_strcmp(data->cmd->arg[0], "exit"))
		data->status = ft_exit();
    else if (!ft_strcmp(data->cmd->arg[0], "echo"))
		data->status = ft_echo(data);
	else if (!ft_strcmp(data->cmd->arg[0], "export"))
        data->status = ft_export(*shell->cmd, shell);
    else if(!ft_strcmp(data->cmd->arg[0], "man"))
        data->status = ft_man(data);
    else if (ft_strcmp(data->cmd->arg[0], "cd") == 0)
        data->status = ft_cd(data);
    else
        return(NOT_FOUND);

/*
	if (ft_strcmp(current->cmd->arg[0], "unset") == 0)
		ft_unset(current);
 	else
		printf("cmd not found");
*/
	return (result);
}

void execute_command(t_shell *shell)
{

    find_cmd(shell);

    if (is_bin(*shell))
    {
        data->status = exec_builts_in(shell);
    }
    else
        printf("%s: command not found\n", shell->cmd->arg[0]);
}
