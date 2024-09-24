LIBFT_DIR		= libft/
LIBS			= -lft -lreadline

NAME			= minishell

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra -I./includes -I./usr/include/readline -g \
	# -fsanitize=address,undefined
RM				= rm -rf

SRC_DIR			= src/
OBJ_DIR			= obj/

FILES_SRC		= 	main.c 						\
					parsing/lexer.c 			\
					parsing/tokenizator.c 		\
					parsing/setter.c			\
					parsing/create_lists.c		\
					parsing/printer.c			\
					parsing/quote_stuff.c 		\
					parsing/utils1.c			\
					parsing/expand_variables.c	\
					parsing/create_env_lists.c	\
					parsing/exp_utils.c			\
					parsing/fill_struct.c		\
					parsing/syntaxis.c			\
					parsing/file_des.c			\
					parsing/fill_utils.c		\
					parsing/expand_utils.c		\
					parsing/stock_var.c			\
					exec/exec_com.c				\
					exec/exec_utils.c			\
					exec/BIN/ft_export.c		\
					exec/BIN/ft_echo.c			\
					exec/BIN/ft_env.c			\
					exec/BIN/ft_exit.c			\
					exec/BIN/ft_man.c			\
					exec/BIN/ft_pwd.c			\
					exec/BIN/ft_cd.c			\


SRC 			= $(addprefix $(SRC_DIR),$(FILES_SRC))
OBJ_SRC 		= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

vpath %.c $(SRC_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ_SRC)
	@$(MAKE) -s all -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJ_SRC) -L $(LIBFT_DIR) $(LIBS) $(LDFLAGS) -o $@

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re