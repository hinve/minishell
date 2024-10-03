/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:26:24 by mjeannin          #+#    #+#             */
/*   Updated: 2024/10/02 14:28:28 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	recognize_var(char *cmd)
{
	if (ft_strchr(cmd, '=') != NULL)
	{
		printf("Setting variable: %s\n", cmd);
		return (1);
	}
	if (ft_strncmp(cmd, "$", 1) == 0)
	{
		printf("Referencing variable: %s\n", cmd);
		return (2);
	}
	printf("Not a variable command: %s\n", cmd);
	return (0);
}
