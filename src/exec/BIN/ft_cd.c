#include "minishell.h"

void ft_cd(char *path)
{
    char cwd[1024];

    if (path == NULL || ft_strlen(path) == 0)
    {
        ft_printf("cd: missing argument\n");
        return;
    }
    if (chdir(path) != 0)
    {
        ft_printf("cd: %s: %s\n", path, strerror(errno));
        return;
    }
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        setenv("PWD", cwd, 1);
    }
    else
    {
        ft_printf("cd: error retrieving current directory: %s\n", strerror(errno));
    }
}