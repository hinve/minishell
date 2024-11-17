
#include "minishell.h"

void handle_redirections(t_cmd *cmd)
{
    int fd;

    // Handle input redirection
    if (cmd->fdin != -1 && cmd->fdin < cmd->n_args)
    {
        fd = open(cmd->arg[cmd->fdin], O_RDONLY);
        if (fd == -1)
        {
            perror("open");
            exit(1);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }

    if (cmd->fdout != -1 && cmd->fdout < cmd->n_args)
    {
        fd = open(cmd->arg[cmd->fdout], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            perror("open");
            exit(1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }

    // Handle append redirection
    if (cmd->append != -1 && cmd->append < cmd->n_args)
    {
        fd = open(cmd->arg[cmd->append], O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
        {
            perror("open");
            exit(1);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
}

void execute(t_shell *data)
{
    if (is_built_in(data) == 1)
    {
        exec_built_in(data);
        return;
    }
    else if (command_exists(data->cmd->arg[0]))
    {
        handle_redirections(data->cmd);
        find_cmd(data);
        return;
    }
    else
    {
        status(data, 127);
        print_error_status(data);
    }
    return;
}

void restart_fds(int saved_stdin, int saved_stdout)
{
    // Restore the original stdin
    if (dup2(saved_stdin, STDIN_FILENO) == -1)
    {
        perror("dup2");
        exit(1);
    }
    close(saved_stdin);

    // Restore the original stdout
    if (dup2(saved_stdout, STDOUT_FILENO) == -1)
    {
        perror("dup2");
        exit(1);
    }
    close(saved_stdout);
}

void set_pid(t_shell *data)
{
    t_cmd *current = data->cmd;
    while (current)
    {
        current->pid = malloc(sizeof(pid_t) * current->n_args);
        if (!current->pid)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        current = current->next;
    }
}

void end_processes(t_shell *data)
{
    int status;
    pid_t pid;

    while ((pid = wait(&status)) > 0)
    {
        if (WIFEXITED(status))
        {
            data->status = WEXITSTATUS(status);
        }
        else if (WIFSIGNALED(status))
        {
            data->status = 128 + WTERMSIG(status);
        }
    }
}

void executor(t_shell *data)
{
    int tmpin;
    int tmpout;
    int fdpipe[2];
    int i;
    t_cmd *current;

    set_pid(data);
    current = data->cmd;
    if (!current)
        return;
    tmpin = dup(0);
    tmpout = dup(1);
    if (current->fdin == -1)
        current->fdin = dup(tmpin);
    i = 0;
    while (current)
    {
        if (current->next && strcmp(current->arg[current->n_args - 1], "|") == 0)
        {
            if (pipe(fdpipe) == -1)
            {
                perror("pipe");
                exit(1);
            }
            current->fdout = fdpipe[1];
            current->next->fdin = fdpipe[0];
        }
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(1);
        }
        else if (pid == 0)
        {
            if (current->fdin != -1)
            {
                dup2(current->fdin, STDIN_FILENO);
                close(current->fdin);
            }
            if (current->fdout != -1)
            {
                dup2(current->fdout, STDOUT_FILENO);
                close(current->fdout);
            }
            handle_redirections(current);
            execute(data);
            exit(data->status);
        }
        else
        {
            current->pid[i] = pid;
            if (current->fdin != -1)
                close(current->fdin);
            if (current->fdout != -1)
                close(current->fdout);
        }
        current = current->next;
        i++;
    }

    int j = 0;
    current = data->cmd;
    while (j < data->cmd->n_args)
    {
        waitpid(current->pid[j], &data->status, 0);
        data->status = WEXITSTATUS(data->status);
        j++;
    }

    end_processes(data);
    restart_fds(tmpin, tmpout);
}