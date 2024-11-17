/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:33:43 by mjeannin          #+#    #+#             */
/*   Updated: 2024/11/17 15:33:56 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_status(t_shell *data)
{
	if (data->status == 127)
		printf("%s : command not found\n", data->cmd->arg[0]);
	return;
}

int    status(t_shell *data, int status)
{
	return (data->status = status);
}