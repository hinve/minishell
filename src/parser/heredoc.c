/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:25:52 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/01 18:27:37 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_heredoc(char *expanded_line, t_cmd *cmd)
{
	write(cmd->fdin, expanded_line, ft_strlen(expanded_line));
	write(cmd->fdin, "\n", 1);
}

void	heredoc_handler(int signum)
{
	(void)signum;
	printf("\n");
	exit(130);
}

void	save_heredoc(t_cmd *cmd, t_token **tok, t_env *env)
{
	char	*line;
	char	*expanded_line;
	int		i;

	i = 1;
	cmd->fdin = open("hdoc.tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (cmd->fdin == -1)
		printf("Error making HEREDOC\n");
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
		{
			printf("minishell: warning: here-document at line %d"
			" delimited by (wanted «%s»)\n", i, (*tok)->content);
			break ;
		}
		i++;
		add_history(line);
		expanded_line = expand_heredoc(line, env);
		if (ft_strncmp(line, (*tok)->content, ft_strlen((*tok)->content)
				+ 1) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc(expanded_line, cmd);
		free(line);
	}
}
