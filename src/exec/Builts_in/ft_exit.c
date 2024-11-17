#include "minishell.h"

int is_valid_atoi(char *str)
{
    if (!str || *str == '\0')
        return (0);
    if (*str == '-' || *str == '+')
        str++;
    while (*str)
    {
        if (!isdigit(*str))
            return (0);
        str++;
    }
    return (1);
}

void ft_exit(t_shell *data)
{
    printf("exit\n");

    if (data->cmd->n_args > 1)
    {
        if (is_valid_atoi(data->cmd->arg[1]))
        {
            status(data, ft_atoi(data->cmd->arg[1]) % 256);
        }
        else
        {
            printf("Minishell: exit: %s: numeric argument required\n", data->cmd->arg[1]);
            status(data, 2);
        }
    }
    else
    {
        status(data, 0);
    }
    exit(data->status);
}