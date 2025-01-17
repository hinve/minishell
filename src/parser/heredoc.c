/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpino-mo <hpino-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:25:52 by mjeannin          #+#    #+#             */
/*   Updated: 2025/01/14 12:42:26 by hpino-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_heredoc(char *line, t_cmd *cmd)
{
	write(cmd->fdin, line, ft_strlen(line));
	write(cmd->fdin, "\n", 1);
}

static void	here_doc(char *limit, t_cmd *cmd, t_env *env)
{
	char	*line;
	int		len;

	len = ft_strlen(limit);
	line = readline("> ");
	while (line)
	{
		if (ft_strncmp(line, limit, len) == 0 && !line[len])
		{
			write_heredoc(line, cmd);
			free(line);
			break ;
		}
		line = expand_heredoc(line, env);
		if (line)
		{
			write_heredoc(line, cmd);
			free(line);
		}
		line = readline("> ");
	}
	if (!line)
		exit(1);
	exit(0);
}

void	save_heredoc(t_cmd *cmd, t_token **tok, t_env *env)
{
	pid_t	pid;

	*tok = (*tok)->next;
	if (cmd->error == 0)
	{
		if (cmd->fdin > 2)
			close(cmd->fdin);
		cmd->fdin = open("hdoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		pid = fork();
		if (pid == 0)
		{
			handle_ctrl_c();
			here_doc((*tok)->content, cmd, env);
		}
		else if (pid > 0)
			wait_hd(*tok, cmd);
	}
	unlink("hdoc.tmp");
	*tok = (*tok)->next;
}
