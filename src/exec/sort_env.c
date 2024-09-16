#include "minishell.h"

int is_valid_env(char *arg)
{
    int i;

    if (!arg || !arg[0])
        return 0;

    if (arg[0] != '_' && !isalpha(arg[0]))
        return 0;

    i = 1;
    while (arg[i] && arg[i] != '=')
    {
        if (arg[i] != '_' && !isalnum(arg[i]))
            return 0;
        i++;
    }

    if (arg[i] == '=')
        return 1;

    return 2;
}

int str_env_len(t_env *env)
{
    int i = 0;
    while (env)
    {
        i++;
        env = env->next;
    }
    return (i);
}

void sort_env(t_env **env)
{
    int env_len = str_env_len(*env);
    int ordered = 0;
    t_env *current;
    t_env *next;
    char *tmp_key;
    char *tmp_value;
    int i;

    while (ordered == 0)
    {
        ordered = 1;
        current = *env;
        next = current->next;
        i = 0;
        while (i < env_len - 1)
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
            i++;
        }
        env_len--;
    }
}

void print_sorted_env(t_env *env)
{
    sort_env(&env);
    while (env)
    {
        ft_printf("declare -x %s=%s\n", env->key, env->value);
        env = env->next;
    }
}