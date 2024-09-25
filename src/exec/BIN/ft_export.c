#include "minishell.h"

// Helper function to check if an argument is a valid environment variable
int is_valid_argument(const char *arg)
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
    return 1;
}

// Helper function to print an error message
void print_error(const char *arg, const char *msg)
{
    write(STDERR_FILENO, "export: `", 9);
    write(STDERR_FILENO, arg, strlen(arg));
    write(STDERR_FILENO, "': ", 3);
    write(STDERR_FILENO, msg, strlen(msg));
    write(STDERR_FILENO, "\n", 1);
}

// Helper function to add or update an environment variable
void env_put_var(t_env **env, const char *arg)
{
    char *key;
    char *value;
    char *equal_sign;
    t_env *existing_var;

    equal_sign = strchr(arg, '=');
    if (equal_sign)
    {
        key = strndup(arg, equal_sign - arg);
        value = strdup(equal_sign + 1);
    }
    else
    {
        key = strdup(arg);
        value = NULL;
    }

    existing_var = find_env_var(*env, key);
    if (existing_var)
    {
        free(existing_var->value);
        existing_var->value = value;
    }
    else
    {
        t_env *new_var = malloc(sizeof(t_env));
        new_var->key = key;
        new_var->value = value;
        new_var->next = *env;
        *env = new_var;
    }
}

// Helper function to find an environment variable by key
t_env *find_env_var(t_env *env, const char *key)
{
    while (env)
    {
        if (strcmp(env->key, key) == 0)
            return env;
        env = env->next;
    }
    return NULL;
}

// Helper function to print the environment variables in sorted order
void print_sorted_env(t_env *env)
{
    t_env *sorted_env = NULL;
    t_env *current;
    t_env *min;
    t_env **min_prev;
    t_env **prev;

    while (env)
    {
        min = env;
        min_prev = &env;
        prev = &env->next;
        current = env->next;
        while (current)
        {
            if (strcmp(current->key, min->key) < 0)
            {
                min = current;
                min_prev = prev;
            }
            prev = &current->next;
            current = current->next;
        }
        *min_prev = min->next;
        min->next = sorted_env;
        sorted_env = min;
    }

    current = sorted_env;
    while (current)
    {
        if (current->value)
            ft_printf("declare -x %s=\"%s\"\n", current->key, current->value);
        else
            ft_printf("declare -x %s\n", current->key);
        current = current->next;
    }

    while (sorted_env)
    {
        current = sorted_env;
        sorted_env = sorted_env->next;
        if (current->key)
            free(current->key);
        if (current->value)
            free(current->value);
        free(current);
    }
}

int ft_export(t_cmd cmd, t_shell data)
{
    int status;
    int i;
    t_env *currentenv = data.env;
    char **argv = cmd.arg;

    status = EXIT_SUCCESS;
    if (!argv[1])
    {
        print_sorted_env(currentenv);
        return (status);
    }
    i = 1;
    while (argv[i])
    {
        if (!is_valid_argument(argv[i]))
        {
            print_error(argv[i], "not a valid identifier");
            status = EXIT_FAILURE;
        }
        else
        {
            env_put_var(&currentenv, argv[i]);
        }
        i++;
    }
    return (status);
}