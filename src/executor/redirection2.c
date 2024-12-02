/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:36:26 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/02 17:36:57 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_infile(t_cmd *cmd, t_token **tok)
{
	t_cmd	*last;

	last = get_last_cmd(cmd);
	(*tok) = (*tok)->next;
	if (last->fdin > 2)
		close(last->fdin);
	if (cmd->fdin == -1)
		cmd->fdin = open((*tok)->content, O_RDONLY);
	if (cmd->fdin == -1)
	{
		perror("Error: reading fd");
		return (1);
	}
	(*tok) = (*tok)->next;
	return (0);
}

int	save_append(t_cmd *cmd, t_token **tok)
{
	t_cmd	*last;

	last = get_last_cmd(cmd);
	(*tok) = (*tok)->next;
	if (last->fdout > 2)
		close(last->fdout);
	if (last->fdout == -1)
		last->fdout = open((*tok)->content, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (last->fdout == -1)
	{
		perror("Error: appending fd");
		return (1);
	}
	(*tok) = (*tok)->next;
	return (0);
}
