

#include "minishell.h"
/*
typedef struct s_cmd // ----> Estructura para trabajar commandos
{
	char	**arg; // comando con sus flags
	int		n_args; // numero de argumentos en el nodo: ej: echo -n sería 2
    int fdin;
    int fdout;
    struct s_cmd *next; // puntero al siguiente nodo (comando)
}	t_cmd;
*/


int		exec_bin(t_cmd cmd, t_shell shell)
{

	int		result;
    t_shell *currentshell = &shell;
    t_cmd   *currentcmd = &cmd;
 //   t_env   *currentenv = shell.env;

	result = 0;

    if (ft_strcmp(currentcmd->arg[0], "pwd") == 0)
		result = ft_pwd();
    if (ft_strcmp(currentcmd->arg[0], "env") == 0)
		ft_env(currentshell->env);
    else
        ft_printf("Input is no recognized\n");
/*	if (ft_strcmp(current->cmd->arg[0], "echo") == 0)
		ft_echo(current);
	if (ft_strcmp(current->cmd->arg[0], "cd") == 0)
		ft_cd(current);

	if (ft_strcmp(current->cmd->arg[0], "export") == 0)
		ft_export(current);
	if (ft_strcmp(current->cmd->arg[0], "unset") == 0)
		ft_unset(current);*/
//	else
//		printf("cmd not found");

	return (result);
}

void execute_command(t_shell *shell)
{
    t_shell *current = shell;


        int i = 0;
        while (i < current->cmd->n_args)
        {
           if (current->cmd == NULL)
            {
                return;
            }
            exec_bin(*current->cmd, *shell);
            i++;
            current->cmd = current->cmd->next;
        }
    return ;

}
