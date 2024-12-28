/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_des.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:57:33 by mjeannin          #+#    #+#             */
/*   Updated: 2024/12/28 13:07:25 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    save_append(t_cmd *cmd, t_token **tok)
{
    (*tok) = (*tok)->next;
    cmd->fdout = open((*tok)->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (cmd->fdout == -1)
        printf("Error appending fd\n");
    *tok = (*tok)->next;
    return (0);
}

int    save_infile(t_cmd *cmd, t_token **tok)
{
    (*tok) = (*tok)->next;
    cmd->fdin = open((*tok)->content, O_RDONLY);
    if (cmd->fdin == -1)
        printf("Error reading fd\n");
    (*tok) = (*tok)->next;
    return (0);
}

int    save_outfile(t_cmd *cmd, t_token **tok)
{
    (*tok) = (*tok)->next;
    if (cmd->fdout > 2)
        close(cmd->fdout);
    cmd->fdout = open((*tok)->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (cmd->fdout == -1)
        printf("Error opening fd\n");
    *tok = (*tok)->next;
    return (0);
}

int    ft_innout(t_cmd *cmd, t_token **tok, t_env *env)
{
    if (cmd == NULL || tok == NULL)
    {
        printf("Invalid pointer\n");
        return 1;
    }
    if ((*tok)->type == IN)
        save_infile(cmd, tok);
    else if ((*tok)->type == OUT)
        save_outfile(cmd, tok);
    else if ((*tok)->type == APPEND)
        save_append(cmd, tok);
    else if ((*tok)->type == HEREDOC)
        save_heredoc(cmd, tok, env);
    return 0;
}
