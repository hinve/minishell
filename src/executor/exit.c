/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 11:44:30 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/02 11:49:11 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	isnum(char *str)
{
	if (!str || str == (void *)0)
		return (-1);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit((unsigned char)*str))
			return (0);
		str++;
	}
	return (1);
}

void	ft_exit(t_cmd *cmd)
{
	int	exit_code;

	exit_code = 1;
	if (cmd->n_args > 2)
		perror("exit: too many arguments");
	else if (cmd->n_args == 2)
	{
		if (isnum(cmd->arg[1]) == 0)
		{
			printf("%s%s%s", "exit: ", cmd->arg[1], \
			" numeric argument required\n");
			exit(255);
		}
		exit_code = ft_atoi(cmd->arg[1]);
	}
	printf("exit\n");
	exit(exit_code);
}
