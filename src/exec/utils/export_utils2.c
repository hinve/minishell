/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:20:14 by mjeannin          #+#    #+#             */
/*   Updated: 2024/11/21 15:26:27 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_argument(const char *arg)
{
	int	i;

	if (!arg || !arg[0])
		return (0);
	if (arg[0] != '_' && !ft_isalpha(arg[0]))
		return (0);
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] != '_' && !ft_isalnum(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	print_error(const char *arg, const char *msg)
{
	write(STDERR_FILENO, "export: `", 9);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "': ", 3);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
}

void	update_existing_var(t_env *existing_var, char *value, char *key)
{
	free(existing_var->value);
	existing_var->value = value;
	free(key);
}

void	add_new_var(t_env **env, char *key, char *value)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (new_var != NULL)
	{
		new_var->key = key;
		new_var->value = value;
		new_var->next = *env;
		*env = new_var;
	}
}

void	split_key_value(const char *arg, char **key, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign != NULL)
	{
		*key = ft_strndup(arg, equal_sign - arg);
		*value = ft_strdup(equal_sign + 1);
	}
	else
	{
		*key = ft_strdup(arg);
		*value = NULL;
	}
}
