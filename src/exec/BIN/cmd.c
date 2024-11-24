/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 14:23:25 by matta             #+#    #+#             */
/*   Updated: 2024/11/24 15:57:09 by mjeannin         ###   ########.fr       */
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

int execute_command(char *cmd, char **argv, char **envp, int pipefd[2])
{
    pid_t pid = fork();
    if (pid == 0)
    {
        // Child process
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execve(cmd, argv, envp);
        exit(4);
    }
    else if (pid < 0)
    {
        printf("Error: fork failed\n");
        return (5);
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
        int status;
        waitpid(pid, &status, 0);
        return status;
    }
}

int handle_absolute_path(t_shell *data, int pipefd[2])
{
    char **argv = set_argv(data);
    char **envp = convert_env_to_array(data->env);
    if (!envp)
    {
        printf("Error: Failed to convert environment variables\n");
        return (3);
    }
    int status = execute_command(data->cmd->arg[0], argv, envp, pipefd);
    free_split(envp);
    free(argv);
    return status;
}

static int search_in_path(t_shell *data, int pipefd[2])
{
    char **stack = ft_split(data->path, ':');
    if (!stack)
    {
        printf("Error: Failed to split PATH\n");
        return 1;
    }
    int i = 0;
    while (stack[i] != NULL)
    {
        char *full_path;
		full_path = malloc(strlen(stack[i]) + strlen(data->cmd->arg[0]) + 2);
        if (!full_path)
        {
            printf("Error: malloc failed\n");
            free_split(stack);
            return 2;
        }
        strcpy(full_path, stack[i]);
        strcat(full_path, "/");
        strcat(full_path, data->cmd->arg[0]);
        int status = execute_command(full_path, set_argv(data), convert_env_to_array(data->env), pipefd);
        free(full_path);
        if (status == 0)
        {
            free_split(stack);
            return 0;
        }
        i++;
    }
    free_split(stack);
    return (status(data, 127)); // Command not found
}

int find_cmd(t_shell *data)
{
    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        printf("Error: pipe failed\n");
        return 6;
    }
    if (data->cmd->arg[0][0] == '/')
    {
        return handle_absolute_path(data, pipefd);
    }
    data->path = get_value(data->env, "PATH");
    return (search_in_path(data, pipefd));
}