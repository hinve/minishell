/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matta <matta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 00:02:42 by matta             #+#    #+#             */
/*   Updated: 2024/08/29 10:41:12 by matta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

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

void ft_echo(char **args)
{
    int i = 1;
    while (args[0])
    {
        printf("%s ", args[i]);
        i++;
    }
    printf("\n");
}

void ft_cd(char **args)
{
    if (args[1])
        printf("Changing directory to: %s\n", args[1]);
    else
        printf("No directory specified\n");
}

void ft_pwd(char **args)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("Current working directory: %s\n", cwd);
    else
        perror("getcwd() error");

    if (args[1])
        printf("Additional argument: %s\n", args[1]);
    else
        printf("No additional argument provided\n");
}

void ft_env(char **args)
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

void ft_export(char **args)
{
    if (args[1])
        printf("Exporting: %s\n", args[1]);
    else
        printf("No variable specified\n");
}

void ft_unset(char **args)
{
    if (args[1])
        printf("Unsetting: %s\n", args[1]);
    else
        printf("No variable specified\n");
}