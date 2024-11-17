#include "minishell.h"

void print_error_status(t_shell *data)
{
    if (data->status == 127)
        printf("%s : command not found\n", data->cmd->arg[0]);
    data->status = 0;
    return;
}
