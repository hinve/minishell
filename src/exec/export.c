#include "minishell.h"

void ft_export(t_cmd cmd, t_env *env)
{
    t_env   *new;
    t_env   *current = env;
    char *var = cmd.arg[1];
    char *value = strchr(var, '=');
    *value = '\0'; 
    value++;

    if (cmd.n_args < 2)
    {
        write(STDERR_FILENO, "export: not enough arguments\n", 29);
        return;
    }
        if (value == NULL)
    {
        write(STDERR_FILENO, "export: invalid format, expected VAR=VALUE\n", 44);
        return;
    }
    while (current)
    {
        if (strcmp(current->key, var) == 0)
        {
            free(current->value);
            current->value = strdup(value);
            return;
        }
        current = current->next;
    }

    new = malloc(sizeof(t_env));
    if (!new)
    {
        perror("malloc");
        return;
    }
    new->key = strdup(var);
    if (!new->key)
    {
        free(new);
        perror("strdup");
        return;
    }
    new->value = strdup(value);
    if (!new->value)
    {
        free(new->key);
        free(new);
        perror("strdup");
        return;
    }
    new->next = env->next;
    env->next = new;
}
