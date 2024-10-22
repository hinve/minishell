
#include "minishell.h"

int		exec_bin(t_shell *shell)
{

	int		result;

	result = 0;

    if (!ft_strcmp(shell->cmd->arg[0], "pwd"))
		result = ft_pwd();
    else if (!ft_strcmp(shell->cmd->arg[0], "env"))
            ft_env(shell);
    else if (!ft_strcmp(shell->cmd->arg[0], "exit"))
		ft_exit();
    else if (!ft_strcmp(shell->cmd->arg[0], "echo"))
		ft_echo(shell);
	else if (!ft_strcmp(shell->cmd->arg[0], "export"))
        ft_export(*shell->cmd, shell);
    else if(!ft_strcmp(shell->cmd->arg[0], "man"))
        ft_man(shell);
    else if (ft_strcmp(shell->cmd->arg[0], "cd") == 0)
        ft_cd(shell);
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


    find_cmd(shell);

    if (is_bin(*shell))
    {
        exec_bin(shell);
    }
    else
        printf("%s: command not found\n", shell->cmd->arg[0]);
}
