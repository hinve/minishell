
#include "minishell.h"


int recognize_var(char *cmd)
{
    if (strchr(cmd, '=') != NULL)
    {
        printf("Setting variable: %s\n", cmd);
        return 1; // Variable to set
    }

    if (strncmp(cmd, "$", 1) == 0)
    {
        printf("Referencing variable: %s\n", cmd);
        return 2; // Variable to reference
    }

    printf("Not a variable command: %s\n", cmd);
    return 0; // Not a variable command
}
