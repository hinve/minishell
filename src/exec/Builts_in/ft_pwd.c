#include "minishell.h"

int ft_pwd(t_shell *data)
{
	char	cwd[500];

	if (data->cmd->n_args > 1)
	{
		printf("pwd : too many arguments\n");
		return (status(data, 1));
	}
	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, 1);
		return (status(data, 0));
	}
	else
		return (status(data, 1));
}