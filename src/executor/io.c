/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:32:12 by mjeannin          #+#    #+#             */
/*   Updated: 2025/02/04 16:32:59 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_input(int fdin)
{
	if (dup2(fdin, 0) == -1)
	{
		perror("Error: dup2 failed for input redirection");
		exit(1);
	}
	close(fdin);
}

void	redirect_output(int fdout, int tmpout)
{
	if (fdout == -1)
	{
		fdout = dup(tmpout);
		if (fdout == -1)
		{
			perror("Error: dup failed for output redirection");
			exit(1);
		}
	}
	if (dup2(fdout, 1) == -1)
	{
		perror("Error: dup2 failed for output redirection");
		exit(1);
	}
	close(fdout);
}
