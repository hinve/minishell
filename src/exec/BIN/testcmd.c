static char	*generate_full_path(char *path, char *arg)
{
	char	*path_slash;
	char	*full_path;

	path_slash = ft_strjoin(path, "/");
	full_path = ft_strjoin(path_slash, arg);
	free(path_slash);
	return (full_path);
}

static void	find_executable_in_path(t_shell *shell, char **args, char **paths)
{
	char	*full_path;
	int		i;
	bool	found;

	found = false;
	i = 0;
	while (paths && paths[i] && !found)
	{
		full_path = generate_full_path(paths[i++], args[0]);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
			execve(full_path, args, shell->env);
		else if (access(full_path, F_OK) == 0)
		{
			ft_permission_denied(shell, full_path);
			found = true;
		}
		free(full_path);
	}
	free_array(&paths);
	if (!found)
		ft_command_not_found_error(shell, args[0]);
}

static void	directly_executable(t_shell *shell, char **args)
{
	if (access(args[0], F_OK) == 0 && is_directory(shell, args[0]))
		ft_is_a_directory_error(shell, args[0]);
	else if (access(args[0], F_OK) == 0 && access(args[0], X_OK) == 0)
		execve(args[0], args, shell->env);
	else if (access(args[0], F_OK) == 0)
		ft_permission_denied(shell, args[0]);
	else
		ft_command_not_found_error(shell, args[0]);
}

void	execute_bin(t_shell *shell, char **args)
{
	char	*path_env;
	char	**paths;

//	shell->exit_status = 0;
	update_envp(shell);
	if (args[0][0] == '.' || args[0][0] == '/')
		directly_executable(shell, args);
	else
	{
		path_env = get_value(shell, "PATH");
		if (path_env)
		{
			paths = ft_split(path_env, ':');
			free(path_env);
			find_executable_in_path(shell, args, paths);
		}
		else
			ft_minishell_error(shell, "-minishell: PATH not set");
	}
}