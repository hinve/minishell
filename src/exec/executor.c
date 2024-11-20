
#include "minishell.h"

int pipes_or_redir(char *line)
{
    if (ft_strstr(line, "|") || ft_strstr(line, ">") || ft_strstr(line, "<") || ft_strstr(line, ">>") || strstr(line, "<<"))
    {
        return (1); // Found pipes or redirections
    }
    return (0); // No pipes or redirections found
}

void execute(t_shell *data)
{
    if (is_built_in(data) == 1)
    {
        exec_built_in(data);
        status(data, 0);
        return;
    }
    else if (command_exists(data->cmd->arg[0]))
    {
        find_cmd(data);
        status(data, 0);
        return;
    }
    else
    {
        status(data, 127);
        print_error_status(data);
    }
    return;
}

void executor(t_shell *data)
{
    if (pipes_or_redir(data->cmd->arg[0]))
        handle_pipes(data);
    else
        execute(data);
}