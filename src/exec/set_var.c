#include "minishell.h"

void    var_declaration(t_shell data)
{
    t_cmd *currentcmd = data.cmd;
    t_env *current = data.var;
    t_env *prev = NULL;
    t_env *new_var = (t_env *)malloc(sizeof(t_env));
    char *value = currentcmd->arg[2];

    printf("var declaration");
    while (current)
    {
        if (ft_strcmp(current->key, currentcmd->arg[1]) == 0)
        {
            free(current->value);
            current->value = ft_strdup(value);
            return;
        }
        prev = current;
        current = current->next;
    }
    if (!new_var)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    new_var->key = ft_strdup(currentcmd->arg[1]);
    new_var->value = ft_strdup(value);
    new_var->next = NULL;

    if (prev)
        prev->next = new_var;
    else
        data.var = new_var;
}