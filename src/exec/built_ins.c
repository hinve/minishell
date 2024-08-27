
#include "minishell.h"

void mycd(const char *path)
{
    if (path == NULL)
    {
        ft_printf("mycd: missing argument\n");
        return;
    }

    if (chdir(path) != 0)
    {
        ft_printf("mycd: %s: %s\n", path, strerror(errno));
    }
}

void myexit(t_shell *data, char **args) 
{
    int exit_status = 0;

    if (args[1] != NULL)
    {
        exit_status = ft_atoi(args[1]);
    }

    if (data->str_cmd)
    {
        free(data->str_cmd);
    }
    ft_clear_structs(&data->token, &data->cmd);

    exit(exit_status);
}