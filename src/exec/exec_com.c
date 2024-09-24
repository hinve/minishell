

#include "minishell.h"

void check_env_values(t_env *env)
{
    t_env *current = env;
    
    if (!current)
        printf("naze\n");
    while (current)
    {
        printf("Key: %s, Value: %s\n", current->key, current->value);
        current = current->next;
    }

}

int		exec_bin(t_cmd cmd, t_shell shell)
{

	int		result;
    t_cmd   *currentcmd = &cmd;
    t_env   *currentenv = shell.env;
 //   t_env   *currentvar = shell.var;

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
        ft_cd(currentcmd->arg[1]);
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
    exec_bin(*current->cmd, *shell);

}
