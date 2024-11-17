
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

# define BUFF_SIZE 4096

# define STDIN      0
# define STDOUT     1
# define STDERR     2
# define NOT_EXEC   126
# define NOT_FOUND  127
# define TERMD      130
# define SEG_FAULT  139

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
# include <stdbool.h>
# include <dirent.h>
# include <sys/types.h>



//*--------------------LEXER--------------------------------
void	lexer(char *str_cmd, t_token **tok);
void	set_token(int type, char *str_cmd, t_token **tok, int *i);
void	setter(int type, char *str_cmd, t_token **tok, int *i);
void	create_list(int type, t_token **tok, char *content);
void	print_lists(t_token *tok);
int		quote_stuff(int *i, char *str_cmd);
int		dquote_stuff(int *i, char *str_cmd);
int		quote_count(char *str);
void	heredoc_in(char *str_cmd, t_token **tok, int *i);
void	append_out(char *str_cmd, t_token **tok, int *i);
//*--------------------PARSER-------------------------------
void	parser(t_token **tok, char **envp, t_env *env);
//*--------------------EXPAND_VARIABLES---------------------
void	expand_variables(t_shell *data);
void	create_env_list(char *value, t_env **env, char *key);
int     is_there_a_dollar(char *str);
char    *replace_dollar(char *str, t_shell *data);
t_env	*transform_env(char *envp[]);
//*--------------------FILL_STRUCT--------------------------
void	fill_struct(t_shell *data);
int     syntaxis_is_ok(t_token **token);
t_cmd	*list_empty_fill(t_token **token, int argcs);
void	add_back_fill(t_cmd **lst, t_cmd *new);
t_cmd	*ft_last_fill(t_cmd *lst);
//*--------------------UTILS2-------------------------------
char	*get_value(t_env *env, const char *key);
char *quote_union(char *str);
char *own_get_env(char *key);

//*--------------------FDS----------------------------------
void    ft_innout(t_cmd *cmd, t_token **tok);
char	*expand_heredoc(char *line);
char    *expand_utils(char *line, char *temp, int *i, int *temp_len);

//....................EXECUTOR..............................
void    executor(t_shell *data);
//-------------------BUILTS_IN------------------------------
int     is_built_in(t_shell *data);
int		exec_built_in(t_shell *data);
int     ft_pwd(void);
int		ft_env(t_shell *data);
void    ft_exit(t_shell *data);
int     ft_echo(t_shell *data);
int     ft_man(t_shell *data);
int     ft_cd(t_shell *data);
int     ft_export(t_shell *data);
int     builtin_export(t_shell *data);
int     ft_unset(t_shell *data);
//-------------------------CMD-------------------------------
int     find_cmd(t_shell *data);
void    exec_cmd(char *loc, char *cmd, t_shell *data);
char    **convert_env_to_array(t_env *env);
void	execute_bin(t_shell *shell, char **args);
int     command_exists(const char *cmd);

//------------------ENV----------------------------
void    check_env_values(t_env *env);
int		env_add(const char *value, t_env *env);
char	*get_env_name(char *dest, const char *src);
int     is_valid_argument(const char *arg);
void    print_error(const char *arg, const char *msg);
void    env_put_var(t_env **env, const char *arg);
t_env   *find_env_var(t_env *env, const char *key);
void    print_sorted_env(t_env *env);
int     str_env_len(t_env *env);
void    sort_env(t_env **env);
int     is_valid_env(char *arg);
int		is_in_env(t_env *env, char *args);

//----------------------EXEC_UTILS--------------------------
void    print_error_status(t_shell *data);




//-------------------INIT-----------------------------------
void    print_banner();
//-------------------VAR------------------------------------
int     recognize_var(char *cmd);
int     is_cmd_in_varname(t_cmd *cmd, t_env *var_list);
void    print_variable(t_env *var, char *key);
int     is_key_in_env(t_shell data);

//-------------------INIT_EXPORT-------------------------------
void    init_export(t_shell *data);
//--------------------EXEC_PATH------------------------------
int    is_in_path(t_shell *shell);
void   exec_path_cmd(t_shell *shell);
int    exec_path(t_shell data);

//-------------------ENV------------------------------------

#endif