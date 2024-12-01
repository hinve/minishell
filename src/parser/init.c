/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:24:42 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/01 18:25:28 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_shell *data, char **envp)
{
	data->token = NULL;
	data->cmd = NULL;
	data->env = NULL;
	data->export = NULL;
	data->str_cmd = NULL;
	data->envp = envp;
	data->path = NULL;
	data->status = 0;
	data->pid = NULL;
	data->cmd_count = 0;
}

void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	init(t_shell *data, char **envp)
{
	init_signals();
	init_struct(data, envp);
	init_env(data, envp);
}
