
#include "minishell.h"


void execute_command(t_shell *data)
{
    if (is_built_in(data) == 1)
    {
        printf("ping execute_command 2\n");
        data->status = exec_built_in(data);
        return;
    }
    else
    {
        find_cmd(data);
        return;
    } 
    printf("%s: command not found\n", data->cmd->arg[0]);
    data->status = 127;
    return;
}
