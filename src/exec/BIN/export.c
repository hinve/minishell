#include "minishell.h"

/* void ft_export(t_cmd cmd, t_env *env)
{
    t_env *new;
    t_env *current = env;
    char *var;
    char *value;

    if (cmd.n_args < 2)
    {
        write(STDERR_FILENO, "export: not enough arguments\n", 29);
        return;
    }

    var = strdup(cmd.arg[1]);
    if (!var) {
        perror("strdup");
        return;
    }

    value = strchr(var, '=');
    if (value == NULL) {
        write(STDERR_FILENO, "export: invalid format, expected VAR=VALUE\n", 44);
        free(var);
        return;
    }

    *value = '\0';
    value++;

    while (current) {
        if (strcmp(current->key, var) == 0) {
            free(current->value);
            current->value = strdup(value);
            free(var);
            return;
        }
        current = current->next;
    }

    new = malloc(sizeof(t_env));
    if (!new) {
        perror("malloc");
        free(var);
        return;
    }
    new->key = strdup(var);
    if (!new->key) {
        free(new);
        free(var);
        perror("strdup");
        return;
    }
    new->value = strdup(value);
    if (!new->value) {
        free(new->key);
        free(new);
        free(var);
        perror("strdup");
        return;
    }
    new->next = env->next;
    env->next = new;
    free(var);
}

---------------- */

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
		get_env_name(env_name, env->value);
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
        print_sorted_env(vars);
        return (0);
    }
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

