/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matteo <matteo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 00:02:42 by matta             #+#    #+#             */
/*   Updated: 2024/09/02 21:30:50 by matteo           ###   ########.fr       */
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

void ft_echo(t_cmd cmd)
{
 
    int i = 1;

    while (cmd.arg[i] != NULL)
    {
        printf("%s", cmd.arg[i]);
        if (i == cmd.n_args)
            ft_printf("\n");
        else
            printf(" ");
        i++;
    }
    printf("\n");
}

void    ft_exit()
{
    ft_printf("Hasta luegi !\n");
    exit (1);
}

int ft_env(t_env *env)
{
    t_env   *current = env;

    if (!current || !current->value || current->value[0] == '\0')
    {
        ft_printf("Value is empty or not set\n");
        return (1);
    }
    while (current)
    {
        ft_putendl(current->value);
        ft_printf("%s", current->value);
        current = current->next;
    }
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