/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 00:02:42 by matta             #+#    #+#             */
/*   Updated: 2024/08/29 15:57:45 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "limits.h"
/*
	result = 0;
	if (ft_strcmp(args[0], "echo") == 0)
		result = ft_echo(args);
	if (ft_strcmp(args[0], "cd") == 0)
		result = ft_cd(args, mini->env);
	if (ft_strcmp(args[0], "pwd") == 0)
		result = ft_pwd();
	if (ft_strcmp(args[0], "env") == 0)
		ft_env(mini->env);
	if (ft_strcmp(args[0], "export") == 0)
		ft_export(args, mini->env, mini->secret_env);
	if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(args, mini);
*/
/*
void ft_echo(t_shell shell)
{
    int i = 1;
    while (args[0])
    {
        printf("%s ", args[i]);
        i++;
    }
    printf("\n");
}

void ft_cd(t_shell shell)
{
    if (args[1])
        printf("Changing directory to: %s\n", args[1]);
    else
        printf("No directory specified\n");
}

void ft_env(t_shell shell)
{
    extern char **environ;
    for (char **env = environ; *env != 0; env++)
    {
        char *thisEnv = *env;
        printf("%s\n", thisEnv);
    }

    // Use the function input to print something
    if (args[1])
        printf("Additional argument: %s\n", args[1]);
    else
        printf("No additional argument provided\n");
}

void ft_export(t_shell shell)
{
    if (args[1])
        printf("Exporting: %s\n", args[1]);
    else
        printf("No variable specified\n");
}

void ft_unset(t_shell shell)
{
    if (args[1])
        printf("Unsetting: %s\n", args[1]);
    else
        printf("No variable specified\n");
}
*/
int		ft_env(t_env *env)
{
	while (env && env->next != NULL)
	{
		ft_putendl(env->value);
		env = env->next;
	}
	if (env)
		ft_putendl(env->value);
	return (0);
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