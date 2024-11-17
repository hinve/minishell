/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpino-mo <hpino-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:01:51 by hpino-mo          #+#    #+#             */
/*   Updated: 2024/11/17 17:02:38 by hpino-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredoc(t_token **tok, int fd)
{
	char	*line;
	char	*expanded_line;

	line = readline("> ");
	while (line != NULL)
	{
		if (ft_strncmp(line, (*tok)->content, ft_strlen((*tok)->content)
				+ 1) == 0)
		{
			free(line);
			break ;
		}
		expanded_line = expand_heredoc(line);
		write(fd, expanded_line, ft_strlen(expanded_line));
		write(fd, "\n", 1);
		free(line);
		free(expanded_line);
		line = readline("> ");
	}
}

void	save_heredoc(t_cmd *cmd, t_token **tok)
{
	int	fd;

	*tok = (*tok)->next;
	fd = open("heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error creating HEREDOC file");
		return ;
	}
	handle_heredoc(tok, fd);
	close(fd);
	fd = open("heredoc.tmp", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening HEREDOC file");
		return ;
	}
	cmd->fdin = fd;
	*tok = (*tok)->next;
}
