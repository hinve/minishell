

#include "minishell.h"

int		exec_bin(t_cmd cmd, t_shell shell)
{

	int		result;
    t_cmd   *currentcmd = &cmd;
    t_env   *currentenv = shell.env;

	result = 0;


    if (!ft_strcmp(currentcmd->arg[0], "pwd"))
		result = ft_pwd();
    else if (!ft_strcmp(currentcmd->arg[0], "env"))
            ft_env(currentenv);
    else if (!ft_strcmp(currentcmd->arg[0], "exit"))
		ft_exit();
    else if (!ft_strcmp(currentcmd->arg[0], "echo"))
		ft_echo(*currentcmd);
	else if (!ft_strcmp(currentcmd->arg[0], "export"))
        ft_export(*currentcmd, shell);
    else if(!ft_strcmp(currentcmd->arg[0], "man"))
        ft_man(*currentcmd);
    else if (ft_strcmp(currentcmd->arg[0], "cd") == 0)
        ft_cd(&shell, &cmd);
    else
        ft_printf("command not found\n");

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
    t_shell *current = shell;
// ----> aqui plantear un if para determinar si es un builtin o otro
    if (is_bin(*shell))
        exec_bin(*current->cmd, *shell);
}
