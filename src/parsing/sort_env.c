#include "minishell.h"

typedef struct s_env
{
    char			*key;
    char			*value;
    struct s_env	*next;
}	t_env;

int str_env_len(t_env *env)
{
    int i = 0;
    while (env)
    {
        i++;
        env = env->next;
    }
    return i;
}

void sort_env(t_env **env)
{
    int env_len = str_env_len(*env);
    int ordered = 0;
    t_env *current;
    t_env *next;
    char *tmp_key;
    char *tmp_value;

    while (ordered == 0)
    {
        ordered = 1;
        current = *env;
        next = current->next;
        for (int i = 0; i < env_len - 1; i++)
        {
            if (strcmp(current->key, next->key) > 0)
            {
                tmp_key = current->key;
                tmp_value = current->value;
                current->key = next->key;
                current->value = next->value;
                next->key = tmp_key;
                next->value = tmp_value;
                ordered = 0;
            }
            current = next;
            next = next->next;
        }
        env_len--;
    }
}

void print_sorted_env(t_env *env)
{
    sort_env(&env);
    while (env)
    {
        printf("declare -x %s=%s\n", env->key, env->value);
        env = env->next;
    }
}