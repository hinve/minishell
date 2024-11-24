
#include "minishell.h"

/* void add_arg(t_shell *data)
{
    char **new_arg = fd_to_args(data->cmd->fdin);
}

void remove_node(t_shell *data)
{
    t_cmd *temp;
    
    temp = data->cmd;
    if (data == NULL || data->cmd == NULL)
    {
        return;
    }
    data->cmd = data->cmd->next;
    free(temp);
} */

void execute(t_shell *data)
{
    if (is_built_in(data) == 1)
    {
        exec_built_in(data);
        return;
    }
    else if (command_exists(data->cmd->arg[0]))
    {
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

/* void exec_pipe(t_shell *data)
{
    if (data->fdin != -1)
        add_arg(data);
    execute(data);
    remove_node(data);
} */

void executor(t_shell *data)
{
    execute(data);
/* 
    if (is_pipe(data))
        find_cmd(data);
    else
        execute;
*/
}