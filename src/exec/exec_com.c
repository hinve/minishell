
#include "minishell.h"

int		exec_builts_in(t_shell *data)
{

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
    return(0);

}

void execute_command(t_shell *data)
{
//    find_cmd(shell);

    if (is_bin(*data))
    {
        data->status = exec_builts_in(data);
        return;
    }
/*     else
        find_cmd(shell); */
    else
        printf("%s: command not found\n", data->cmd->arg[0]);
    data->status = 127;
}
