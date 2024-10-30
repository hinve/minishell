/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:23:25 by matta             #+#    #+#             */
/*   Updated: 2024/10/25 12:00:43 by mjeannin         ###   ########.fr       */
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

char    **set_argv(t_shell *data)
{
    int i;
    char **argv = malloc((data->cmd->n_args + 1) * sizeof(char *));
    if (!argv)
    {
        printf("Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }
    i = 0;
    while(i < data->cmd->n_args)
    {
        argv[i] = data->cmd->arg[i];
        i++;
    }
    argv[i] = NULL;
    
    return (argv);
}

int    find_cmd(t_shell *data)
{
    char **stack;
    int i = 0;
    pid_t pid;
    int status;

    data->path = get_value(data->env, "PATH");
    stack = ft_split(data->path, ':');
    while (stack[i] && stack[i][0] != '\0')
    {
        char *full_path = malloc(strlen(stack[i]) + strlen(data->cmd->arg[0]) + 2); // +2 for '/' and '\0'
        if (!full_path)
        {
            printf("Error: malloc failed\n");
            free_split(stack);
            return (0);
        }

        // Manually build the full path using strcpy and strcat
        ft_strncpy(full_path, stack[i], ft_strlen(full_path));  // Copy "stack[i]" to full_path
        strcat(full_path, "/");       // Append '/' to full_path
        strcat(full_path, data->cmd->arg[0]);       // Append "cmd" to full_path
        
        pid = fork();
        if (pid == 0)
        {
            char **argv = set_argv(data);
            char **envp = convert_env_to_array(data->env);
            if (!envp)
            {
                printf("Error: Failed to convert exit variables\n");
                exit(EXIT_FAILURE);
            }
            execve(full_path, argv, envp);
            free(full_path);
            free_split(envp);
            free(argv);
            exit(EXIT_FAILURE);
        }
        else if (pid < 0)
        {
            // Fork failed
            printf("Error: fork failed\n");
            free(full_path);
            free_split(stack);
            return (0);
        }
        else
        {
            // Parent process
            waitpid(pid, &status, 0);
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
            {
                free(full_path);
                free_split(stack);
                return (0);
            }
        }

        free(full_path);
        i++;
    }

    free_split(stack);
    printf("Command not found: %s\n", data->cmd->arg[0]);
    data->status = 127;
    return (127); // Command not found
}
