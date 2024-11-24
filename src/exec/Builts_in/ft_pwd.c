/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:48:24 by mjeannin          #+#    #+#             */
/*   Updated: 2024/11/21 12:03:40 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_shell *data)
{
	char	cwd[500];

	if (data->cmd->n_args > 1)
	{
		printf("pwd : too many arguments\n");
		return (status(data, 1));
	}
	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, 1);
		return (status(data, 0));
	}
	else
		return (status(data, 1));
}
