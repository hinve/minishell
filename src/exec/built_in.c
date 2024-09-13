/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matteo <matteo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 00:02:42 by matta             #+#    #+#             */
/*   Updated: 2024/09/13 08:28:01 by matteo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "limits.h"

/*

void ft_cd(t_shell shell)
{
    if (args[1])
        printf("Changing directory to: %s\n", args[1]);
    else
        printf("No directory specified\n");
}



void ft_unset(t_shell shell)
{
    if (args[1])
        printf("Unsetting: %s\n", args[1]);
    else
        printf("No variable specified\n");
}
*/

char *get_env_value(t_env *env, const char *key)
{
    t_env *current = env;
    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void ft_echo(t_cmd cmd)
{
    int i = 1;
    int newline = 1;

    if (cmd.n_args > 1 && strcmp(cmd.arg[1], "-n") == 0)
    {
        newline = 0;
        i = 2;
    }
    while (i < cmd.n_args)
    {
        write(STDOUT_FILENO, cmd.arg[i], ft_strlen(cmd.arg[i]));
        if (i < cmd.n_args - 1)
        {
            write(STDOUT_FILENO, " ", 1);
        }
        i++;
    }
    if (newline)
    {
        write(STDOUT_FILENO, "\n", 1);
    }
}

void ft_exit()
{
    printf("Hasta luegi !\n");
    exit(1);
}

int ft_env(t_env *env)
{
    t_env *current = env;

    if (!current || !current->value || current->value[0] == '\0')
    {
        printf("Value is empty or not set\n");
        return 1;
    }
    while (current)
    {
        printf("%s\n", current->value);
        current = current->next;
    }
    return 0;
}

int ft_pwd(void)
{
    char	cwd[500];

	if (getcwd(cwd, 500))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	else
		return (1);
}