#include "minishell.h"

void ft_export(t_cmd cmd, t_env *env)
{
    t_env *new;
    t_env *current = env;
    char *var;
    char *value;

    if (cmd.n_args < 2)
    {
        write(STDERR_FILENO, "export: not enough arguments\n", 29);
        return;
    }

    var = strdup(cmd.arg[1]);
    if (!var) {
        perror("strdup");
        return;
    }

    value = strchr(var, '=');
    if (value == NULL) {
        write(STDERR_FILENO, "export: invalid format, expected VAR=VALUE\n", 44);
        free(var);
        return;
    }

    *value = '\0';
    value++;

    while (current) {
        if (strcmp(current->key, var) == 0) {
            free(current->value);
            current->value = strdup(value);
            free(var);
            return;
        }
        current = current->next;
    }

    new = malloc(sizeof(t_env));
    if (!new) {
        perror("malloc");
        free(var);
        return;
    }
    new->key = strdup(var);
    if (!new->key) {
        free(new);
        free(var);
        perror("strdup");
        return;
    }
    new->value = strdup(value);
    if (!new->value) {
        free(new->key);
        free(new);
        free(var);
        perror("strdup");
        return;
    }
    new->next = env->next;
    env->next = new;
    free(var);
}
