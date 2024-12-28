/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 10:39:01 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/27 10:40:13 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arg(char ***matrix)
{
	int	i;

	if (!matrix || !*matrix)
		return ;
	i = 0;
	while ((*matrix)[i])
	{
		free((*matrix)[i]);
		(*matrix)[i] = NULL;
		i++;
	}
	free(*matrix);
	*matrix = NULL;
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*aux;

	if (!cmd || !*cmd)
		return ;
	while (*cmd)
	{
		aux = (*cmd)->next;
		if ((*cmd)->fdin > 2)
			close((*cmd)->fdin);
		if ((*cmd)->fdout > 2)
			close((*cmd)->fdout);
		free_arg(&((*cmd)->arg));
		free(*cmd);
		*cmd = aux;
	}
}

void	free_cmd_list(t_cmd **cmd_list)
{
	if (!cmd_list || !*cmd_list)
		return ;
	free_cmd(cmd_list);
	*cmd_list = NULL;
}
