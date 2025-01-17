/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpino-mo <hpino-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:23:46 by mjeannin          #+#    #+#             */
/*   Updated: 2025/01/14 12:47:20 by hpino-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal;

void	is_line_is_empty(char *str)
{
	free(str);
	str = readline(M "Mini" W "shell" G "--> " RST);
}

void	handle_empty_or_whitespace_commands(char **str_cmd)
{
	if (!ft_strlen(*str_cmd) || only_spaces(*str_cmd) == 1)
	{
		free(*str_cmd);
		*str_cmd = readline(M "Mini" W "shell" G "--> " RST);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	data;

	init(&data, envp);
	while (1)
	{
		process_user_input(&data);
		handle_empty_or_whitespace(&data);
		process_commands(&data);
	}
	free_all(&data);
	return ((void)argc, (void)argv, 0);
}
