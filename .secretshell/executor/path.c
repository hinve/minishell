#include "minishell.h"

static void	access_cmd(t_shell *data)
{
    if (access(data->cmd->arg[0], X_OK) == 0)
    {
        data->path = data->cmd->arg[0];
        return ;
    }
}

void	get_path(t_shell *data, t_cmd *cmd)
{
	char	**content_splited;
	int		i;
	char	*path;
	char	*content;
    
    i = -1;
	access_cmd(data);
    content = get_value(data->env, "PATH");
	if (!content)
		return ;
	content_splited = ft_split(content, ':');
	while (content_splited[++i] != NULL)
	{
		path = ft_strjoin(content_splited[i], "/");
		path = ft_strjoin(path, cmd->arg[0]);
		if (access(path, X_OK) == 0)
        {
            data->path = path;
			return ;
        }
	}
	return ;
}
