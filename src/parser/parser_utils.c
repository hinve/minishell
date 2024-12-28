/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:23:14 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/01 18:24:30 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	only_spaces(char *str_cmd)
{
	int	i;

	i = 0;
	while (str_cmd[i])
	{
		if (str_cmd[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
