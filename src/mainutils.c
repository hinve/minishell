/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpino-mo <hpino-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:35:09 by hpino-mo          #+#    #+#             */
/*   Updated: 2024/11/17 16:35:36 by hpino-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(t_shell *data, char **envp)
{
	data->token = NULL;
	data->cmd = NULL;
	data->env = NULL;
	data->var = NULL;
	data->envp = envp;
	data->status = 0;
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

void	handle_ctrld(char *str_cmd)
{
	if (str_cmd == NULL)
	{
		printf("exit\n");
		exit(0);
	}
}

void	process_command(t_shell *data)
{
	if (data->token != NULL && syntaxis_is_ok(&data->token) == 1)
	{
		expand_variables(data);
		fill_struct(data);
		execute_command(data);
	}
}

void	read_command(t_shell *data)
{
	data->str_cmd = readline(M "Mini" W "shell" G "--> " RST);
	handle_ctrld(data->str_cmd);
	add_history(data->str_cmd);
}
