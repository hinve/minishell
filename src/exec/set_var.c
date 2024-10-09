#include "minishell.h"

void    update_var(t_shell data)
{
    t_env *current = data.env;

    while (current)
    {
        if (ft_strcmp(current.key, data.cmd.arg[0]))
        {
            free(current->value);
            current->value = ft_strdup(data.cmd->arg[1]);
            return ;
        }
        current = current->next;
    }
    current = data.var;
        while (current)
    {
        if (ft_strcmp(current.key, data.cmd.arg[0]))
        {
            free(current->value);
            current->value = ft_strdup(data.cmd->arg[1]);
            return ;
        }
        current = current->next;
    }
    return ;
}

void set_var(t_shell data) {
    if (data.cmd->arg[0] == NULL || data.cmd->arg[1] == NULL) {
        printf("Usage: set_var <key> <value>\n");
        return;
    }

    char *key = data.cmd->arg[0];
    char *value = data.cmd->arg[1];
    t_env *current = find_var(data.var, key);

    if (current) {
        free(current->value);
        current->value = strdup(value);
    } else {
        t_env *new_var = malloc(sizeof(t_env));
        if (!new_var) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        new_var->key = strdup(key);
        new_var->value = strdup(value);
        new_var->next = data.var;
        data.var = new_var;
    }
}

void    var_declaration(t_shell data)
{
    if (is_key_in_env(data.cmd, data.var))
        update_var(data);
    else
        set_var(data);
}
