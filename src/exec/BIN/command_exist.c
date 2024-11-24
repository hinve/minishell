/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:47:30 by mjeannin          #+#    #+#             */
/*   Updated: 2024/11/24 15:43:25 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *get_next_path(char **start)
{
    if (start == NULL || *start == NULL)
    {
        return NULL;
    }

    char *end = strchr(*start, ':');
    char *path;

    if (end != NULL)
    {
        *end = '\0';
        path = *start;
        *start = end + 1;
    }
    else
    {
        path = *start;
        *start = NULL;
    }

    return path;
}

int check_command_in_dir(const char *dir, const char *cmd)
{
    char *full_path = malloc(strlen(dir) + strlen(cmd) + 2);
    if (!full_path)
    {
        perror("malloc");
        return 0;
    }

    strcpy(full_path, dir);
    strcat(full_path, "/");
    strcat(full_path, cmd);

    int result = access(full_path, X_OK) == 0;
    free(full_path);
    return result;
}

int check_paths(char *path_env, const char *cmd)
{
    char *start = path_env;
    char *path;

    while ((path = get_next_path(&start)) != NULL)
    {
        if (check_command_in_dir(path, cmd))
        {
            return 1;
        }
    }
    return 0;
}

int command_exists(const char *cmd)
{
    if (cmd == NULL || *cmd == '\0')
    {
        return 0;
    }

    if (strchr(cmd, '/') != NULL)
    {
        return access(cmd, X_OK) == 0;
    }

    char *path_env = getenv("PATH");
    if (path_env == NULL)
    {
        return 0;
    }

    char *path_env_copy = strdup(path_env);
    if (path_env_copy == NULL)
    {
        perror("strdup");
        return 0;
    }

    int result = check_paths(path_env_copy, cmd);
    free(path_env_copy);
    return result;
}
