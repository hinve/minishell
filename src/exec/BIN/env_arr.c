/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:05:05 by matta             #+#    #+#             */
/*   Updated: 2024/11/17 18:27:36 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_array(char **env_array)
{
	int	i;

	i = 0;
	while (env_array[i] != NULL)
	{
		printf("%s\n", env_array[i]);
		i++;
	}
}

int	count_env_vars(t_env *env)
{
	int count;
	
	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

char **allocate_env_array(int count)
{
	char **env_array = malloc((count + 1) * sizeof(char *));
	if (!env_array)
	{
		perror("malloc");
		return NULL;
	}
	return (env_array);
}

int populate_env_array(t_env *env, char **env_array)
{
    int i = 0;
    while (env)
    {
        size_t len = strlen(env->key) + strlen(env->value) + 2; // +2 for '=' and '\0'
        env_array[i] = malloc(len);
        if (!env_array[i])
        {
            while (i > 0)
            {
                free(env_array[--i]);
            }
            free(env_array);
            return 0;
        }
        strcpy(env_array[i], env->key);
        strcat(env_array[i], "=");
        strcat(env_array[i], env->value);
        i++;
        env = env->next;
    }
    env_array[i] = NULL; 
    return 1;
}

char	**convert_env_to_array(t_env *env)
{
	int count; 
	char **env_array; 

	count = count_env_vars(env);
	env_array = allocate_env_array(count);
	if (!env_array)
		return (NULL);
	if (!populate_env_array(env, env_array))
		return (NULL);
	return (env_array);
}
