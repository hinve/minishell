#include "minishell.h"

void update_env_var(t_env *env, const char *key, const char *value)
{
    t_env *current = env;

    // Traverse the linked list to find the key
    while (current != NULL)
    {
        if (ft_strcmp(current->key, (char *)key) == 0)
        {
            // Free the old value and assign the new value
            free(current->value);
            current->value = ft_strdup(value);
            if (!current->value)
            {
                ft_printf("cd: memory allocation error\n");
            }
            return;
        }
        current = current->next;
    }

    // If the key does not exist, add a new node to the list
    t_env *new_node = (t_env *)malloc(sizeof(t_env));
    if (!new_node)
    {
        ft_printf("cd: memory allocation error\n");
        return;
    }
    new_node->key = ft_strdup(key);
    new_node->value = ft_strdup(value);
    if (!new_node->key || !new_node->value)
    {
        printf("cd: memory allocation error\n");
        free(new_node->key);
        free(new_node->value);
        free(new_node);
        return;
    }
    new_node->next = env;
    env = new_node;
}

void ft_cd(t_shell *data)
{
    char *path;
    char cwd[1024];

    if (data->cmd->n_args < 2 || ft_strlen(data->cmd->arg[1]) == 0)
    {
        ft_printf("cd: missing argument\n");
        return;
    }
    path = data->cmd->arg[1];

    if (ft_strcmp(path, "..") == 0)
    {
        if (chdir("..") != 0)
        {
            ft_printf("cd: %s: %s\n", path, strerror(errno));
            return;
        }
    }
    else
    {
        if (chdir(path) != 0)
        {
            ft_printf("cd: %s: %s\n", path, strerror(errno));
            return;
        }
    }
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        update_env_var(data->env, "PWD", cwd);
    }
    else
    {
        ft_printf("cd: error retrieving current directory: %s\n", strerror(errno));
    }
}