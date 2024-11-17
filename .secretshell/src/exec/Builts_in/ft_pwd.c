#include "minishell.h"

int ft_pwd(void)
{
    char	cwd[500];

	if (getcwd(cwd, 500))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	else
		return (1);
}