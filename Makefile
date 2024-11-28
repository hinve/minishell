LIBFT_DIR       = libft/
LIBS            = -lft -lreadline

NAME            = minishell

CC              = gcc
CFLAGS          = -Wall -Werror -Wextra -Iincludes -g #-fsanitize=address
#LDFLAGS         = -fsanitize=address
RM              = rm -rf

SRC_DIR         = src/
EXEC_DIR        = $(SRC_DIR)executor/
PARSER_DIR      = $(SRC_DIR)parser/
OBJ_DIR         = obj/
OBJ_EXEC_DIR    = $(OBJ_DIR)executor/
OBJ_PARSER_DIR  = $(OBJ_DIR)parser/

FILES_SRC       = main.c

FILES_PARSER    = init.c    	   \
                  lexer.c          \
                  tokenizator.c    \
                  setter.c         \
                  create_lists.c   \
                  printer.c        \
                  quote_stuff.c    \
                  in_out.c         \
                  expand_variables.c\
				  expand_utils.c	\
                  exp_utils.c      \
                  syntaxis.c       \
				  heredoc.c 	   \
				  parser_utils.c

FILES_EXEC      = exec_builtins.c  \
                  exec_utils.c     \
				  token_to_cmd.c   \
				  redirections.c   \
				  free_env.c 	   \
				  free_token.c	   \
				  free_cmd.c	   \
                  free.c           \
                  list_utils.c     \
                  key_value.c      \
                  echo.c           \
                  pwd.c            \
                  cd.c             \
                  env.c            \
                  exit.c           \
                  export.c         \
                  unset.c          \
                  executor.c       \
                  path.c           \
                  printing.c

SRC_MAIN        = $(addprefix $(SRC_DIR),$(FILES_SRC))
SRC_PARSER      = $(addprefix $(PARSER_DIR),$(FILES_PARSER))
SRC_EXEC        = $(addprefix $(EXEC_DIR),$(FILES_EXEC))
SRC             = $(SRC_MAIN) $(SRC_EXEC) $(SRC_PARSER)

OBJ_MAIN        = $(SRC_MAIN:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
OBJ_PARSER      = $(SRC_PARSER:$(PARSER_DIR)%.c=$(OBJ_PARSER_DIR)%.o)
OBJ_EXEC        = $(SRC_EXEC:$(EXEC_DIR)%.c=$(OBJ_EXEC_DIR)%.o)
OBJ_SRC         = $(OBJ_MAIN) $(OBJ_EXEC) $(OBJ_PARSER)

vpath %.c $(SRC_DIR) $(PARSER_DIR) $(EXEC_DIR) 

$(OBJ_PARSER_DIR)%.o: $(PARSER_DIR)%.c
	@mkdir -p $(OBJ_PARSER_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_EXEC_DIR)%.o: $(EXEC_DIR)%.c
	@mkdir -p $(OBJ_EXEC_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_SRC)
	@$(MAKE) -s all bonus printf gnl -C $(LIBFT_DIR)
	$(CC) $(OBJ_SRC) -L $(LIBFT_DIR) $(LIBS) $(LDFLAGS) -o $@

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re