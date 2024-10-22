/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matta <matta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:23:25 by matta             #+#    #+#             */
/*   Updated: 2024/10/22 13:44:24 by matta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_split(char **split)
{
    int i = 0;
    while (split[i] != NULL)
    {
        free(split[i]);
        i++;
    }
    free(split);
}

void    find_cmd(t_shell *data)
{
    char **stack;
    int i = 0;
    pid_t pid;
    int status;

    data->path = get_value(data->env, "PATH");
    stack = ft_split(data->path, ':');
    while (stack[i][0] != '\0')
    {
        char *full_path = malloc(strlen(stack[i]) + strlen(data->cmd->arg[0]) + 2); // +2 for '/' and '\0'
        if (!full_path)
        {
            printf("Error: malloc failed\n");
            free_split(stack);
            return;
        }

        // Manually build the full path using strcpy and strcat
        ft_strncpy(full_path, stack[i], ft_strlen(full_path));  // Copy "stack[i]" to full_path
        strcat(full_path, "/");       // Append '/' to full_path
        strcat(full_path, data->cmd->arg[0]);       // Append "cmd" to full_path

        pid = fork();
        if (pid == 0)
        {
            char *argv[] = {data->cmd->arg[0], NULL};
            char **envp = convert_env_to_array(data->env);
            if (!envp) {
                printf("Error: Failed to convert environment variables\n");
                exit(EXIT_FAILURE);
            }
            execve(full_path, argv, envp);
            free(full_path);
            free_split(envp);
            exit(EXIT_FAILURE);
        }
        else if (pid < 0)
        {
            // Fork failed
            printf("Error: fork failed\n");
            free(full_path);
            free_split(stack);
            return;
        }
        else
        {
            // Parent process
            waitpid(pid, &status, 0);
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
            {
                // Command executed successfully
                free(full_path);
                free_split(stack);
                return;
            }
        }

        free(full_path);
        i++;
    }

    free_split(stack);
    printf("Command not found: %s\n", data->cmd->arg[0]);
    return; // Command not found
}
