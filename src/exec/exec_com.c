

#include "minishell.h"

void ft_clear_structs(t_token **token, t_cmd **cmd)
{
    if (token && *token)
    {
        t_token *current = *token;
        t_token *next;
        while (current)
        {
            next = current->next;
            free(current);
            current = next;
        }
        *token = NULL;
    }

    if (cmd && *cmd)
    {
        t_cmd *current = *cmd;
        t_cmd *next;
        while (current)
        {
            next = current->next;
            free(current);
            current = next;
        }
        *cmd = NULL;
    }
}

void execute_command(t_shell *data, char *input)
{
    char **args = NULL;
    char *token;
    int arg_count = 0;

    token = strtok(input, " \t\n");
    while (token != NULL)
    {
        args = realloc(args, sizeof(char*) * (arg_count + 1));
        if (args == NULL)
        {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        args[arg_count++] = token;
        token = strtok(NULL, " \t\n");
    }
    args = realloc(args, sizeof(char*) * (arg_count + 1));
    if (args == NULL)
    {
        perror("realloc");
        exit(EXIT_FAILURE);
    }
    args[arg_count] = NULL;

    if (arg_count == 0)
    {
        free(args);
        return;
    }
    if (strcmp(args[0], "cd") == 0)
    {
        mycd(args[1]);
        free(args);
        return;
    } 
    else if (strcmp(args[0], "exit") == 0)
    {
        myexit(data, args); // Call myexit function with data and args
        free(args);
        return;
    }
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(args);
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        execvp(args[0], args);
        perror("execvp");
        free(args);
        exit(EXIT_FAILURE);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
    free(args);
}