/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:04:11 by mjeannin          #+#    #+#             */
/*   Updated: 2024/11/21 15:20:26 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*get_sorted_env(t_env *env)
{
	t_env	*sorted_env;
	t_env	*min;

	sorted_env = NULL;
	while (env)
	{
		min = get_min_env(&env);
		min->next = sorted_env;
		sorted_env = min;
	}
	return (sorted_env);
}

void	print_sorted_env(t_env *env)
{
	t_env	*sorted_env;

	sorted_env = get_sorted_env(env);
	print_env_list(sorted_env);
	free_env_list(sorted_env);
}

int	ft_export(t_shell *data)
{
	int		i;
	char	**argv;

	i = 1;
	argv = data->cmd->arg;
	if (!argv[1])
	{
		print_sorted_env(data->env);
		return (status(data, 0));
	}
	while (argv[i])
	{
		if (!is_valid_argument(argv[i]))
		{
			print_error(argv[i], "not a valid identifier");
			return (status(data, 1));
		}
		else
		{
			env_put_var(&(data->env), argv[i]);
		}
		i++;
	}
	return (status(data, 0));
}
