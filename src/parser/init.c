/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:24:42 by mjeannin          #+#    #+#             */
/*   Updated: 2025/02/04 16:23:06 by mjeannin         ###   ########.fr       */
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

void	ctrl_c(void)
{
	if (g_signal == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_signal == 1)
		write(1, "\n", 1);
}

static void	sig_handler(int signal)
{
	if (signal == SIGINT && (g_signal == 0 || g_signal == 1))
		ctrl_c();
	if (signal == SIGQUIT && g_signal == 1)
		ft_putendl_fd("Quit (core dumped)", 2);
}

void	init_signals()
{
	struct sigaction	act;

	act.sa_handler = &sig_handler;
	act.sa_flags = SA_RESTART;
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGINT, &act, NULL) == -1)
		ft_printf("Minishell: Error: sigaction");
	if (g_signal == 0)
	{
		act.sa_handler = SIG_IGN;
		if (sigaction(SIGQUIT, &act, NULL) == -1)
			ft_printf("Minishell: Error: sigaction");
	}
	else if (g_signal == 1)
	{
		act.sa_handler = &sig_handler;
		if (sigaction(SIGQUIT, &act, NULL) == -1)
			ft_printf("Minishell: Error: sigaction");
	}
	act.sa_handler = SIG_IGN;
	if (sigaction(SIGTSTP, &act, NULL) == -1)
		ft_printf("Minishell: Error: sigaction");
}

void	init(t_shell *data, char **envp)
{
	init_signals();
	init_struct(data, envp);
	init_env(data, envp);
}
