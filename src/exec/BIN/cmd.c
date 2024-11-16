/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:23:25 by matta             #+#    #+#             */
/*   Updated: 2024/11/16 14:55:17 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int command_exists(const char *cmd)
{
    char *path_env = getenv("PATH");
    if (!path_env)
    {
        return (0);
    }

    char *path = ft_strdup(path_env);
    if (!path)
    {
        return 0;
    }

    char *start = path;
    char *end = NULL;
    while ((end = ft_strchr(start, ':')) != NULL)
    {
        *end = '\0';

        char *full_path = malloc(strlen(start) + ft_strlen(cmd) + 2); // +2 for '/' and '\0'
        if (!full_path)
        {
            free(path);
            return 0; // Memory allocation failed
        }

        strcpy(full_path, start);
        strcat(full_path, "/");
        strcat(full_path, cmd);

        if (access(full_path, X_OK) == 0)
        {
            free(full_path);
            free(path);
            return 1; // Command found
        }

        free(full_path);
        start = end + 1; // Move to the next directory
    }

    // Check the last directory in PATH
    char *full_path = malloc(strlen(start) + strlen(cmd) + 2); // +2 for '/' and '\0'
    if (!full_path)
    {
        free(path);
        return 0; // Memory allocation failed
    }

    strcpy(full_path, start);
    strcat(full_path, "/");
    strcat(full_path, cmd);

    int result = access(full_path, X_OK) == 0;

    free(full_path);
    free(path);
    return result; // Command found or not
}


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

int find_cmd(t_shell *data)
{
    char **stack;
    int i = 0;
    pid_t pid;
    int status;
    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        printf("Error: pipe failed\n");
        return (6); // Pipe failed
    }

    data->path = get_value(data->env, "PATH");
    stack = ft_split(data->path, ':');
    if (!stack)
    {
        printf("Error: Failed to split PATH\n");
        return (1); // Error splitting PATH
    }

    while (stack[i][0] != '\0')
    {
        char *full_path = malloc(strlen(stack[i]) + strlen(data->cmd->arg[0]) + 2); // +2 for '/' and '\0'
        if (!full_path)
        {
            printf("Error: malloc failed\n");
            free_split(stack);
            return (2); // Malloc failed
        }

        // Manually build the full path using strcpy and strcat
        ft_strncpy(full_path, stack[i], ft_strlen(full_path));  // Copy "stack[i]" to full_path
        strcat(full_path, "/");       // Append '/' to full_path
        strcat(full_path, data->cmd->arg[0]);       // Append "cmd" to full_path
        
        pid = fork();
        if (pid == 0)
        {
            // Child process
            close(pipefd[0]); // Close the read end of the pipe
            dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to the write end of the pipe
            close(pipefd[1]); // Close the write end of the pipe

            char **argv = set_argv(data);
            char **envp = convert_env_to_array(data->env);
            if (!envp)
            {
                printf("Error: Failed to convert environment variables\n");
                free(full_path);
                free_split(stack);
                exit(3); // Failed to convert environment variables
            }
            execve(full_path, argv, envp);
            free(full_path);
            free_split(envp);
            free(argv);
            exit(4); // execve failed
        }
        else if (pid < 0)
        {
            // Fork failed
            printf("Error: fork failed\n");
            free(full_path);
            free_split(stack);
            return (5); // Fork failed
        }
        else
        {
            // Parent process
            close(pipefd[1]); // Close the write end of the pipe
            char buffer[1024];
            ssize_t count;
            while ((count = read(pipefd[0], buffer, sizeof(buffer))) > 0)
            {
                write(STDOUT_FILENO, buffer, count); // Write the output to stdout
            }
            close(pipefd[0]); // Close the read end of the pipe

            waitpid(pid, &status, 0);
            if (status == 0)
            {
                free(full_path);
                free_split(stack);
                return (0); // Command executed successfully
            }

        }

        free(full_path);
        i++;
    }

    free_split(stack);
    data->status = 127;
    return (127); // Command not found
}
