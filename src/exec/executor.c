
#include "minishell.h"


void executor(t_shell *data)
{
    if (is_built_in(data) == 1)
    {
        data->status = exec_built_in(data);
        return;
    }
    else if (command_exists(data->cmd->arg[0]))
    {
        find_cmd(data);
        return ;
    }
    else
    {
        data->status = 127;
        print_error_status(data->status);
    }
    return;
}
