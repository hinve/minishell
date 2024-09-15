#include "minishell.h"

int ft_env(t_env *env)
{
    t_env *current = env;

    if (!current || !current->value || current->value[0] == '\0')
    {
        printf("Value is empty or not set\n");
        return 1;
    }
    while (current)
    {
        printf("%s\n", current->value);
        current = current->next;
    }
    return 0;
}