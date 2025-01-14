LIBFT_DIR		= libft/
LIBS			= -lft -lreadline

NAME			= minishell

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -I./includes -I./usr/include/readline -g \
	# -fsanitize=address,undefined
RM				= rm -rf

SRC_DIR			= src/
OBJ_DIR			= obj/

FILES_SRC		= main.c    \
				parser/init.c    	   \
				parser/lexer.c          \
				parser/tokenizator.c    \
				parser/setter.c         \
				parser/create_lists.c   \
				parser/quote_stuff.c    \
				parser/in_out.c         \
				parser/expand_variables.c\
				parser/expand_utils.c	\
				parser/exp_utils.c      \
				parser/syntaxis.c       \
				parser/heredoc.c 	   \
				parser/parser_utils.c \
				parser/handle_quotes.c \
				parser/fill_struct.c    \
				parser/file_des.c       \
				parser/token_to_cmd.c   \
				parser/token_to_cmd_utils.c   \
				parser/handlers.c	\
				parser/simple_quotes.c         \
				main_utils.c \
				executor/exec_builtins.c  \
				executor/exec_utils.c     \
				executor/free_env.c 	   \
				executor/free_token.c	   \
				executor/free_cmd.c	   \
				executor/free.c           \
				executor/list_utils.c     \
				executor/key_value.c      \
				executor/echo.c           \
				executor/pwd.c            \
				executor/cd.c             \
				executor/env.c            \
				executor/exit.c           \
				executor/export.c         \
				executor/unset.c          \
				executor/executor.c       \
				executor/path.c           \
				executor/printing.c

SRC 			= $(addprefix $(SRC_DIR),$(FILES_SRC))
OBJ_SRC 		= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

vpath %.c $(SRC_DIR)

TOTAL_FILES		= $(words $(FILES_SRC))
COMPILED_FILES	= 0

define progress_bar
	$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES)+1))))
	@echo -n "Compiling $< ["
	@for i in $$(seq 1 $(COMPILED_FILES)); do echo -n "#"; done
	@for i in $$(seq $(COMPILED_FILES) $(TOTAL_FILES)); do echo -n "."; done
	@echo "]"
endef

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(progress_bar)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_SRC)
	@echo "Linking $(NAME)"
	@$(MAKE) -s all -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJ_SRC) -L $(LIBFT_DIR) $(LIBS) $(LDFLAGS) -o $@

clean:
	@echo "Cleaning object files"
	@$(RM) $(OBJ_DIR)

fclean: clean
	@echo "Cleaning executable"
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re