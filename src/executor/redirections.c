/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:53:33 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/02 17:44:21 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_outfile(t_cmd *cmd, t_token **tok)
{
	t_cmd	*last;

	last = get_last_cmd(cmd);
	(*tok) = (*tok)->next;
	if (last->fdout > 2)
		close(last->fdout);
	if (last->fdout == -1)
		last->fdout = open((*tok)->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fdout == -1)
	{
		perror("Error: opening fd");
		return (1);
	}
	*tok = (*tok)->next;
	return (0);
}

static void	handle_child_process(t_cmd *cmd, t_token **tok, t_env *env)
{
	signal(SIGINT, heredoc_handler);
	save_heredoc(cmd, tok, env);
	exit(0);
}

static int	handle_parent_process(t_cmd *cmd)
{
	cmd->fdin = open("hdoc.tmp", O_RDONLY);
	if (cmd->fdin == -1)
	{
		perror("Error: reading temp file");
		return (1);
	}
	unlink("hdoc.tmp");
	signal(SIGINT, sigint_handler);
	return (0);
}

static int	ft_fork(t_cmd *cmd, t_token **tok, t_env *env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("Error: heredoc fork failed");
		return (1);
	}
	*tok = (*tok)->next;
	if (pid == 0)
		handle_child_process(cmd, tok, env);
	*tok = (*tok)->next;
	signal(SIGINT, SIG_IGN);
	waitpid(pid, NULL, 0);
	return (handle_parent_process(cmd));
}

int	ft_innout(t_cmd *cmd, t_token **tok, t_env *env)
{
	int	flag;

	flag = 0;
	if (cmd == NULL || tok == NULL || *tok == NULL)
	{
		perror("Error: invalid pointer");
		return (1);
	}
	if ((*tok)->type == IN)
		flag = save_infile(cmd, tok);
	else if ((*tok)->type == OUT)
		flag = save_outfile(cmd, tok);
	else if ((*tok)->type == APPEND)
		flag = save_append(cmd, tok);
	else if ((*tok)->type == HEREDOC)
		flag = ft_fork(cmd, tok, env);
	else
		return (0);
	return (flag);
}
