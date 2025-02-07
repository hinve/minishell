/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjeannin <mjeannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 12:48:26 by hpino-mo          #+#    #+#             */
/*   Updated: 2025/02/07 15:23:30 by mjeannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "../libft/inc/libft.h"

typedef enum e_token_type
{
	WORD,
	PIPE,
	IN,
	OUT,
	HEREDOC,
	APPEND,
	QUOTE,
	DQUOTE
}					t_token_type;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char			**arg;
	int				n_args;
	int				fdin;
	int				fdout;
	int				error;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_shell
{
	t_token			*token;
	t_cmd			*cmd;
	t_env			*env;
	t_env			*export;
	char			*result;
	char			*str_cmd;
	char			**envp;
	char			*path;
	int				status;
	pid_t			*pid;
	int				cmd_count;
	char			*echo_str;
}					t_shell;

#endif