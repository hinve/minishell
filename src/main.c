/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpino-mo <hpino-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 16:35:04 by hpino-mo          #+#    #+#             */
/*   Updated: 2024/11/17 16:35:38 by hpino-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	data;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	init_struct(&data, envp);
	print_banner();
	data.env = transform_env(envp);
	while (1)
	{
		read_command(&data);
		if (!ft_strlen(data.str_cmd) || only_spaces(data.str_cmd) == 1)
		{
			free(data.str_cmd);
			continue ;
		}
		lexer(data.str_cmd, &data.token);
		process_command(&data);
		free(data.str_cmd);
		clear_structs(&data.token, &data.cmd);
	}
	return ((void)argc, (void)argv, 0);
}
