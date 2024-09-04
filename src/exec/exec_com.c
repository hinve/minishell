

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
//    t_shell *currentshell = &shell;
    t_cmd   *currentcmd = &cmd;
    t_env   *currentenv = shell.env;
    t_var   *currentvar = shell.var;

	result = 0;

    if (1 == recognize_var(currentcmd->arg[0]))
        add_var(currentvar, *currentcmd);
    if (1 == is_cmd_in_varname(currentcmd, currentvar))
        print_variable(currentvar, cmd.arg[1]);
    if (ft_strcmp(currentcmd->arg[0], "pwd") == 0)
		result = ft_pwd();
    if (ft_strcmp(currentcmd->arg[0], "env") == 0)
        if (currentenv && currentenv->value)
            ft_env(currentenv);
    if (ft_strcmp(currentcmd->arg[0], "exit") == 0)
		ft_exit();
    if (ft_strcmp(currentcmd->arg[0], "echo") == 0)
		ft_echo(*currentcmd, currentenv, currentvar);
	if (ft_strcmp(currentcmd->arg[0], "export") == 0)
		ft_export(*currentcmd, currentenv);
    recognize_var(currentcmd->arg[0]);


/* 
	if (ft_strcmp(current->cmd->arg[0], "cd") == 0)
		ft_cd(current);


	if (ft_strcmp(current->cmd->arg[0], "unset") == 0)
		ft_unset(current);*/
/* 	else
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
