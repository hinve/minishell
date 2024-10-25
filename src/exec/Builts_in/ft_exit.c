#include "minishell.h"

void ft_exit(t_shell *data)
{
    printf("Hasta luegi !\n");
    data->status = 1;
    exit(1);
}