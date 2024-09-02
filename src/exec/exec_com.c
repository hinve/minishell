

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

	result = 0;

    if (ft_strcmp(currentcmd->arg[0], "pwd") == 0)
		result = ft_pwd();
    if (ft_strcmp(currentcmd->arg[0], "env") == 0)
        if (currentenv && currentenv->value)
            ft_env(currentenv);
    if (ft_strcmp(currentcmd->arg[0], "exit") == 0)
		ft_exit();
    if (ft_strcmp(currentcmd->arg[0], "echo") == 0)
		ft_echo(*currentcmd);
/*
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

    exec_bin(*current->cmd, *shell);

/*     while (current != NULL)
    {
        if (current->cmd == NULL)
        {
            return;
        }

        int i = 0;
        while (i < current->cmd->n_args)
        {
            // No need to check current->cmd again here
            i++;
        }

        current->cmd = current->cmd->next;
    } */
}
