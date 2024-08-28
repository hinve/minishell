

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

void execute_command(t_shell *shell)
{
    t_shell *current = shell;

    while (current != NULL)
    {
        int i = 0;
        while (i < current->cmd->n_args)
        {
            printf("%s ", current->cmd->arg[i]);
            i++;
        }
        printf("\n");
        current->cmd = current->cmd->next;
    }
}


int		exec_bin(char **args)
{
	int		result;

	result = 0;
	if (ft_strcmp(args[0], "echo") == 0)
	ft_echo(args);
	if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(args);
	if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd(args);
	if (ft_strcmp(args[0], "env") == 0)
		ft_env(args);
	if (ft_strcmp(args[0], "export") == 0)
		ft_export(args);
	if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(args);

	return (result);

}