#include "minishell.h"

int ft_env(t_shell *data)
{
    t_env *current = data->env;

    if (!current || !current->value || current->value[0] == '\0')
    {
        printf("Value is empty or not set\n");
        return 1;
    }
    while (current)
    {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
    return 0;
}