/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 18:25:52 by mjeannin          #+#    #+#             */
/*   Updated: 2025/01/07 14:23:40 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void write_heredoc(char *line, t_cmd *cmd)
{
	write(cmd->fdin, line, strlen(line));
	write(cmd->fdin, "\n", 1);
}

static void	ctrl_c_hd(int sig)
{
    (void)sig;
    printf("\n");
    exit(130);
}

static void	new_handler(int sig)
{
    if (sig == SIGINT)
        ctrl_c_hd(sig);
}

static void	handle_ctrl_c()
{
    struct sigaction	new_act;

    new_act.sa_handler = &new_handler;
    new_act.sa_flags = SA_RESTART;
    sigemptyset(&new_act.sa_mask);
    if (sigaction(SIGINT, &new_act, NULL) == -1)
        perror("Error: sigaction");
}

static void	wait_hd(t_token *tok, t_cmd *cmd)
{
    int	stat;

    waitpid(0, &stat, 0);
    if (WEXITSTATUS(stat) == 130)
    {
        cmd->error = 1;
    }
    else if (WEXITSTATUS(stat) == 1)
    {
        printf("minishell: warning: here-document at line delimited by (wanted «%s»)\n", tok->content);
    }
    close(cmd->fdin);
    cmd->fdin = open("hdoc.tmp", O_RDONLY);
}

static void	here_doc(char *limit, t_cmd *cmd, t_env *env)
{
    char	*line;
    int		len;

    len = strlen(limit);
    line = readline("heredoc> ");
    while (line)
    {
        if (strncmp(line, limit, len) == 0 && !line[len])
        {
            write_heredoc(line, cmd);
            free(line);
            break;
        }
        line = expand_heredoc(line, env);
        if (line)
        {
            write_heredoc(line, cmd);
            free(line);
        }
        line = readline("heredoc> ");
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
