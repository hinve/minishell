/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matta <matta@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 00:02:42 by matta             #+#    #+#             */
/*   Updated: 2024/09/01 04:59:52 by matta            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "limits.h"

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

void ft_exit()
{
    ft_printf("Hasta luegi !\n");
    exit (1);
}


int	ft_env(t_env *env)
{
    t_env   *current = env;
    
	while (current && current->next != NULL)
	{
		ft_putendl(current->value);
        printf("%s", current->value);
		current = current->next;
	}
	if (current)
		ft_putendl(current->value);
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