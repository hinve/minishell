/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpino-mo <hpino-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:45:40 by hpino-mo          #+#    #+#             */
/*   Updated: 2025/01/14 12:45:55 by hpino-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c_hd(int sig)
{
	(void)sig;
	printf("\n");
	exit(130);
}

void	new_handler(int sig)
{
	if (sig == SIGINT)
		ctrl_c_hd(sig);
}

void	handle_ctrl_c(void)
{
	struct sigaction	new_act;

	new_act.sa_handler = &new_handler;
	new_act.sa_flags = SA_RESTART;
	sigemptyset(&new_act.sa_mask);
	if (sigaction(SIGINT, &new_act, NULL) == -1)
		perror("Error: sigaction");
}

void	wait_hd(t_token *tok, t_cmd *cmd)
{
	int	stat;

	waitpid(0, &stat, 0);
	if (WEXITSTATUS(stat) == 130)
	{
		cmd->error = 1;
	}
	else if (WEXITSTATUS(stat) == 1)
	{
		printf("minishell: warning: here-document at line 3 delimited by "
			"(wanted «%s»)\n",
			tok->content);
	}
	close(cmd->fdin);
	cmd->fdin = open("hdoc.tmp", O_RDONLY);
}
