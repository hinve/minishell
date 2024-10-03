/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:28:42 by mjeannin          #+#    #+#             */
/*   Updated: 2024/10/02 14:43:13 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_env_len(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void sort_env(t_env **env)
{
    int env_len;
    int ordered;
    t_env *current;
    t_env *next;
    char *tmp_key;
    char *tmp_value;
    int i;

    env_len = str_env_len(*env);
    ordered = 0;
    while (ordered == 0)
    {
        ordered = 1;
        current = *env;
        next = current->next;
        i = 0;

        while (i < env_len - 1)
        {
            if (ft_strcmp(current->key, next->key) > 0)
            {
                // Swap keys and values
                tmp_key = current->key;
                tmp_value = current->value;
                current->key = next->key;
                current->value = next->value;
                next->key = tmp_key;
                next->value = tmp_value;
                ordered = 0;
            }
            current = next;
            next = next->next;
            i++;
        }
        env_len--;
    }
}

void	print_sorted_env(t_env *env)
{
	sort_env(&env);
	while (env)
	{
		printf("declare -x %s=%s\n", env->key, env->value);
		env = env->next;
	}
}