#ifndef	MINISHELL_H
# define MINISHELL_H

# define RST "\033[0m"		/* Reset to default color */
# define RED "\033[1;31m"	/* Bold Red */
# define G "\033[1;32m"		/* Bold Green */
# define Y "\033[1;33m"		/* Bold Yellow */
# define B "\033[1;34m"		/* Bold Blue */
# define M "\033[1;35m"		/* Bold Magenta */
# define C "\033[1;36m"		/* Bold Cyan */
# define W "\033[1;37m"		/* Bold White */

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
# include <signal.h>

//*--------------------INIT--------------------------------
void	init(t_shell *data, char **envp);
void	init_struct(t_shell *data, char **envp);

//*--------------------LEXER-------------------------------
// lexer.c
void	lexer(char *str_cmd, t_token **tok);
// tokenizator.c
void	set_token(int type, char *str_cmd, t_token **tok, int *i);
// setter.c
void	setter(int type, char *str_cmd, t_token **tok, int *i);
// create_lists.c
void	create_list(int type, t_token **tok, char *content);
// printer.c
void	print_lists(t_token *tok);
void	print_cmd_list(t_cmd *cmd);
// quote_stuff.c
int		quote_stuff(int *i, char *str_cmd);
int		dquote_stuff(int *i, char *str_cmd);
// utils.c
void	heredoc_in(char *str_cmd, t_token **tok, int *i);
void	append_out(char *str_cmd, t_token **tok, int *i);

//*--------------------PARSER-------------------------------
void	parser(t_token **tok, char **envp, t_env *env);

//*--------------------EXPAND_VARIABLES---------------------
// expand_variables.c
void	expand_variables(t_token **token, t_env *env, t_shell *data);

// exp_utils.c
int		is_there_a_dollar(char *str);
char	*expand_utils2(char *line, char *temp, int *i, int *temp_len);
char	*replace_dollar(char *line, t_env *env, t_shell *data);

// expand_utils.c
char	*expand_utils(char *line, char *temp, int *i, int *temp_len);
char	*expand_heredoc(char *line, t_env *env);

// syntaxis.c
int		syntaxis_is_ok(t_token **token);
// parser_main.c
int		only_spaces(char *str_cmd);
void	clear_structs(t_token **token, t_cmd **cmd);
void	init_struct(t_shell *data, char **envp);

//*--------------------HEREDOC--------------------------------
void	heredoc_handler(int signum);
void	save_heredoc(t_cmd *cmd, t_token **tok, t_env *env);
int		heredoc(t_shell *data, t_cmd *cmd, t_token **tok);

//*--------------------SIGNALS--------------------------------
void	init_signals(void);
void	sigint_handler(int signum);

//*--------------------TOKEN-TO-CMD------------------------
void	add_cmd_to_list(t_cmd **head, t_cmd *new_cmd);
t_cmd	*create_cmd_node(void);
void	add_argument(t_cmd *cmd, char *token_content);
int		handle_redirection(t_cmd *cmd, t_token **token, t_env *env);
int		fill_cmd_args(t_cmd *cmd, t_token **token, t_env *env);
int		add_cmd_to_shell(t_cmd **cmd_list, t_token **token, t_env *env);
void	token_to_cmd(t_shell *data);

//*--------------------BUILTINS----------------------------

// exec_builtins.c
int		execute_builtin(t_shell *data);
// cd.c
t_env	*env_lst_search(t_env *env, const char *key);
void	ft_cd(t_shell *data);
// echo.c
void	ft_echo(t_cmd *args);
// env.c
void	ft_env(t_env *env);
// export.c
void	ft_export(t_shell *data);
// exit.c
void	ft_exit(t_cmd *cmd);
// pwd.c
char	*get_current_directory(void);
void	ft_pwd(void);
// unset.c
void	ft_unset(t_shell *data);

//*--------------------ENV---------------------------------

// env.c
void	fill_env_list(t_env **head, char **envp, int *i);
void	init_env(t_shell *data, char **envp);
// list_utils.c
void	add(t_env **head, char *key, char *value);
void	pop(t_env **head, char *key);
t_cmd	*get_last_cmd(t_cmd *cmd);
// key_value.c
void	get_key_value(char *str, char **key, char **value);
char	*get_value(t_env *env, const char *key);
char	*get_cd_value(t_env *env, const char *key);

//*--------------------REDIRECTIONS---------------------------
// file_des.c
int    save_append(t_cmd *cmd, t_token **tok);
int    save_infile(t_cmd *cmd, t_token **tok);
int    save_outfile(t_cmd *cmd, t_token **tok);
int	ft_innout(t_cmd *cmd, t_token **tok, t_env *env);

//*--------------------EXECUTOR----------------------------
// path.c
void	get_path(t_shell *data, t_cmd *cmd);
// executor.c
void	executor(t_shell *data);

//*--------------------UTILS-------------------------------
// exec_utils.c
void	ft_swap(char **a, char **b);
void	count_commands(t_shell *data);
void	init_pid(t_shell *data);
void	end_processess(int *pids, int len);

// printing.c
void	print_key(t_env *head);
char	*print_value(t_env *env, char *key);
void	print_list(t_env *head);
void	print_argu(char **args);

//*--------------------FREE--------------------------------
void	free_env_list(t_env *head);
void	free_env_node(t_env **node);

void	free_token(t_token **token);
void	free_token_list(t_token **token_list);

void	free_arg(char ***matrix);
void	free_cmd(t_cmd **cmd);
void	free_cmd_list(t_cmd **cmd_list);

void	clear_structs(t_token **token, t_cmd **cmd);
void	free_all(t_shell *data);

//*--------------------ERRORS-------------------------------
void fill_struct(t_shell *data);

//*--------------------HANDLE_QUOTES-------------------------------
void	handle_single_quotes(char *str, char *aux, int *i, int *j);
char	*quote_union(char *str);
int quote_count(char *str);
void	handle_double_quotes(char *str, char *aux, int *i, int *j);

//*--------------------MAIN_UTILS----------------------------------
void	process_user_input(t_shell *data);
void	handle_empty_or_whitespace(t_shell *data);
void	process_commands(t_shell *data);
void	minishell(t_shell *data);
void	clear_structs_main(t_token **token, t_cmd **cmd);

#endif