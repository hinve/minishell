#include "minishell.h"

void    ft_man(t_cmd cmd)
{
    if (!ft_strcmp(cmd.arg[1], "echo"))
        ft_printf("echo - display a line of text\n");
    else if (!ft_strcmp(cmd.arg[1], "env"))
        ft_printf("env - run a program in a modified environment\n");
    else if (!ft_strcmp(cmd.arg[1], "exit"))
        ft_printf("exit - cause normal process termination\n");
    else if (!ft_strcmp(cmd.arg[0], "man") && cmd.arg[1] == NULL)
        ft_printf("Which function do you want to see?\n");
    else if (!ft_strcmp(cmd.arg[1], "man"))
        ft_printf("man [func] show you what do\n - echo\n - env\n - exit\n - man\n");
    else
        ft_printf("wrong argument");
}
