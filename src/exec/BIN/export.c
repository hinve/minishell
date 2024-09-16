#include "minishell.h"

static int	print_error(int error, const char *arg)
{
	int		i;

	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", 1);
	else if (error == 0 || error == -3)
		ft_putstr_fd("export: not a valid identifier: ", 1);
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write(1, &arg[i], 1);
		i++;
	}
	write(1, "\n", 1);
	return (1);
}

int			env_add(const char *value, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	if (env && env->value == NULL)
	{
		env->value = ft_strdup(value);
		return (0);
	}
	if (!(new = malloc(sizeof(t_env))))
		return (-1);
	new->value = ft_strdup(value);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (0);
}

char		*get_env_name(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '=' && ft_strlen(src) < BUFF_SIZE)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int			is_in_env(t_env *env, char *args)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];

	get_env_name(var_name, args);
	while (env && env->next)
	{
		get_env_name(env_name, env->key);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			ft_memdel(env->value);
			env->value = ft_strdup(args);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	ft_export(t_cmd cmd, t_env *env, t_env *vars)
{
    int	new_env;
    int	error_ret;
    t_cmd *currentcmd = &cmd;

    new_env = 0;
    if (!currentcmd->arg[1])
    {
        ft_env(env);
        return (0);
    } // check if the argument is correct
    else
    {
        error_ret = is_valid_env(currentcmd->arg[1]);
        if (currentcmd->arg[1][0] == '=')
            error_ret = -3;
        if (error_ret <= 0)
            return (print_error(error_ret, currentcmd->arg[1]));
        if (error_ret == 2)
            new_env = 1;
        else
            new_env = is_in_env(env, currentcmd->arg[1]);
        if (new_env == 0)
        {
            if (error_ret == 1)
                env_add(currentcmd->arg[1], env);
            env_add(currentcmd->arg[1], vars);
        }
    }
    return (0);
}

