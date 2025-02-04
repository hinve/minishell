/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:37:04 by mjeannin          #+#    #+#             */
/*   Updated: 2025/02/04 14:19:51 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_shell *data)
{
	char	*str;
	int		i;

	i = 1;
	while (data->cmd->arg[i])
	{
		str = data->cmd->arg[i];
		pop(&data->env, str);
		pop(&data->export, str);
		i++;
	}
}
