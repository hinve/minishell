#include "minishell.h"

void ft_export(t_cmd cmd, t_env *env) 
{
    if (cmd.n_args < 2)
    {
        write(STDERR_FILENO, "export: not enough arguments\n", 29);
        return;
    }

    char *var = cmd.arg[1];
    char *value = strchr(var, '=');

    if (value == NULL) 
    {
        write(STDERR_FILENO, "export: invalid format, expected VAR=VALUE\n", 44);
        return;
    }

    *value = '\0'; // Split the string into variable name and value
    value++; // Move to the value part

    // Update or add the environment variable in the linked list
    t_env *current = env;
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

    // If the variable was not found, add it to the list
    t_env *new_var = malloc(sizeof(t_env));
    if (!new_var)
    {
        perror("malloc");
        return;
    }
    new_var->key = strdup(var);
    if (!new_var->key)
    {
        free(new_var);
        perror("strdup");
        return;
    }
    new_var->value = strdup(value);
    if (!new_var->value)
    {
        free(new_var->key);
        free(new_var);
        perror("strdup");
        return;
    }
    new_var->next = env->next;
    env->next = new_var;
}