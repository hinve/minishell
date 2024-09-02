
#ifndef MINISHELL_H
# define MINISHELL_H

# define RST "\033[0m"    /* Reset to default color */
# define RED "\033[1;31m" /* Bold Red */
# define G "\033[1;32m"   /* Bold Green */
# define Y "\033[1;33m"   /* Bold Yellow */
# define B "\033[1;34m"   /* Bold Blue */
# define M "\033[1;35m"   /* Bold Magenta */
# define C "\033[1;36m"   /* Bold Cyan */
# define W "\033[1;37m"   /* Bold White */

# include "structures.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>

//*--------------------LEXER-------------------------------
void	lexer(char *str_cmd, t_token **tok);
void	set_token(int type, char *str_cmd, t_token **tok, int *i);
void	setter(int type, char *str_cmd, t_token **tok, int *i);
void	create_list(int type, t_token **tok, char *content);
void	print_lists(t_token *tok);
int		quote_stuff(int *i, char *str_cmd);
int		dquote_stuff(int *i, char *str_cmd);
void	heredoc_in(char *str_cmd, t_token **tok, int *i);
void	append_out(char *str_cmd, t_token **tok, int *i);

//*--------------------PARSER-------------------------------
void	parser(t_token **tok, char **envp, t_env *env);

//*--------------------EXPAND_VARIABLES---------------------
void	expand_variables(t_token **token, char **envp, t_env *env);
void	create_env_list(char *value, t_env **env, char *key);
int     is_there_a_dollar(char *str);
char    *replace_dollar(char *str, t_env *env);
t_env	*transform_env(char *envp[]);


//*--------------------FILL_STRUCT--------------------------
void	fill_struct(t_shell *data);
int     syntaxis_is_ok(t_token **token);
t_cmd	*list_empty_fill(t_token **token, int argcs);
void	add_back_fill(t_cmd **lst, t_cmd *new);
t_cmd	*ft_last_fill(t_cmd *lst);

//*--------------------FDS----------------------------------
void    ft_innout(t_cmd *cmd, t_token **tok);
char	*expand_heredoc(char *line);
char    *expand_utils(char *line, char *temp, int *i, int *temp_len);

//-------------------Executor-------------------------------
void    execute_command(t_shell *data);
int     ft_pwd(void);
int		ft_env(t_env *env);
void    ft_exit();
void    check_env_values(t_env *env);
void    ft_echo(t_cmd cmd);
/*
void    ft_echo(t_shell shell);
void    ft_cd(t_shell shell);
void    ft_export(t_shell shell);
void    ft_unset(t_shell shell);
*/



#endif