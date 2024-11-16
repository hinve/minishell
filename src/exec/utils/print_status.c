#include "minishell.h"

void print_error_status(int status)
{
    if (status == 127)
        printf("Error : command not found\n");
    return;
}
