/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:53:33 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/28 12:29:12 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file(t_token **tok, int flags, int mode)
{
	int	fd;

	fd = open((*tok)->content, flags, mode);
	if (fd == -1)
	{
		perror("Error: opening file");
		return (-1);
	}
	(*tok) = (*tok)->next;
	return (fd);
}

int	save_infile(t_cmd *cmd, t_token **tok)
{
	t_cmd	*last;

	last = get_last_cmd(cmd);
	(*tok) = (*tok)->next;
	if (last->fdin > 2)
		close(last->fdin);
	last->fdin = open_file(tok, O_RDONLY, 0);
	if (last->fdin == -1)
		return (1);
	return (0);
}

int	save_append(t_cmd *cmd, t_token **tok)
{
	t_cmd	*last;

	last = get_last_cmd(cmd);
	(*tok) = (*tok)->next;
	if (last->fdout > 2)
		close(last->fdout);
	last->fdout = open_file(tok, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (last->fdout == -1)
		return (1);
	return (0);
}

int	save_outfile(t_cmd *cmd, t_token **tok)
{
	t_cmd	*last;

	last = get_last_cmd(cmd);
	(*tok) = (*tok)->next;
	if (last->fdout > 2)
		close(last->fdout);
	last->fdout = open_file(tok, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (last->fdout == -1)
		return (1);
	return (0);
}
