# include "minishell.h"

char    *get_value(t_env *env, const char *key)
{
    if (env == NULL || key == NULL)
        perror("Error: null arguments");
    while (env != NULL && env->next != NULL)
    {
        if (!ft_strncmp(env->key, key, ft_strlen(key) + 1))
            return (env->value);
        env = env->next;
    }
    return (NULL);
}

/* char *quote_union(char *str)
{
    int i;
    int q_count;
    int dq_count;

    dq_count = 0;
    q_count = 0;
    i = 0;
    while (str[i])
    {
        if (str[i] == '\'')
            q_count++;
        else if (str[i] == '"')
            dq_count++;
        i++;
    }
    if (q_count % 2 != 0 || dq_count % 2 != 0)
        return (NULL);
    else
    {
        printf("quote union\n");
    }
    return (str);
} */
