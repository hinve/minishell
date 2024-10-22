/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matta <matta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:05:05 by matta             #+#    #+#             */
/*   Updated: 2024/10/21 13:34:13 by matta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_env_array(char **env_array)
{
    int i = 0;
    while (env_array[i] != NULL) {
        printf("%s\n", env_array[i]);
        i++;
    }
}

char    **convert_env_to_array(t_env *env)
{
    int count = 0;
    t_env *current = env;
    char **env_array;
    int i = 0;

    // Count the number of environment variables
    while (current) {
        count++;
        current = current->next;
    }

    // Allocate memory for the array of strings
    env_array = malloc((count + 1) * sizeof(char *));
    if (!env_array) {
        perror("malloc");
        return NULL;
    }

    // Convert each environment variable to a string
    current = env;
    while (current) {
        size_t len = strlen(current->key) + strlen(current->value) + 2; // +2 for '=' and '\0'
        env_array[i] = malloc(len);
        if (!env_array[i]) {
            // Free previously allocated memory on failure
            while (i > 0) {
                free(env_array[--i]);
            }
            free(env_array);
            return NULL;
        }
        snprintf(env_array[i], len, "%s=%s", current->key, current->value);
        i++;
        current = current->next;
    }
    env_array[i] = NULL; // Null-terminate the array
    return env_array;
}