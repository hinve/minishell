#include "minishell.h"

int is_absolute_path(const char *cmd)
{
    return cmd[0] == '/';
}

int check_command_in_dir(const char *dir, const char *cmd)
{
    char *full_path = malloc(strlen(dir) + strlen(cmd) + 2); // +2 for '/' and '\0'
    if (!full_path)
    {
        return 0; // Memory allocation failed
    }

    strcpy(full_path, dir);
    strcat(full_path, "/");
    strcat(full_path, cmd);

    int result = access(full_path, X_OK) == 0;
    free(full_path);
    return result;
}

static int search_in_path(const char *cmd)
{
    char *path_env = getenv("PATH");
    if (!path_env)
    {
        return (0);
    }

    char *path = strdup(path_env);
    if (!path)
    {
        return (0);
    }

    char *start = path;
    char *end = NULL;
    while ((end = strchr(start, ':')) != NULL)
    {
        *end = '\0';
        if (check_command_in_dir(start, cmd))
        {
            free(path);
            return 1;
        }
        start = end + 1;
    }
    int result = check_command_in_dir(start, cmd);
    free(path);
    return result;
}

int command_exists(const char *cmd)
{
    if (is_absolute_path(cmd))
    {
        return (access(cmd, X_OK) == 0);
    }
    return (search_in_path(cmd));
}