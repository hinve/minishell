/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpino-mo <hpino-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:16:09 by hpino-mo          #+#    #+#             */
/*   Updated: 2024/11/17 17:18:40 by hpino-mo         ###   ########.fr       */
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
	int				countPipes;
	int				fdin;
	int				fdout;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_newcmd
{
	char *command;
	int countPipes;
}					t_newcmd;


typedef struct s_shell
{
	t_env			*env;
	t_env			*var;
	t_cmd			*cmd;
	t_newcmd		*newcmd;
	t_env			*export;
	char			*str_cmd;
	int				fdin;
	int				fdout;
	char			**envp;
	const char		*path;
	int				status;
	t_token			*token;
	pid_t			pid;
}					t_shell;

typedef struct s_signal
{
	int				exit_status;
	pid_t			pid;
}					t_signal;

typedef struct s_box
{
	char			*dir;
	struct s_box	*next;
}					t_box;

#endif
