#include "minishell.h"

void free_env_list(t_env *env)
{
    t_env *temp;

    while (env)
    {
        temp = env;
        env = env->next;
        if (temp->key)
        {
            free(temp->key);
            temp->key = NULL;
        }
        if (temp->value)
        {
            free(temp->value);
            temp->value = NULL;
        }
        free(temp);
    }
}

void    free_env_node(t_env **node)
{
    free((*node)->key);
    free((*node)->value);
    free(*node);
    *node = NULL;
}
