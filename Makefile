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
					parsing/utils2.c			\
					exec/executor.c				\
					exec/Builts_in/ft_export.c		\
					exec/Builts_in/ft_echo.c		\
					exec/Builts_in/ft_env.c			\
					exec/Builts_in/ft_exit.c		\
					exec/Builts_in/ft_pwd.c			\
					exec/Builts_in/ft_cd.c			\
					exec/Builts_in/ft_unset.c		\
					exec/Builts_in/built_in_utils.c		\
					exec/BIN/cmd.c					\
					exec/BIN/env_arr.c				\
					exec/BIN/command_exist.c				\
					exec/utils/print_status.c	\
					exec/utils/export_utils.c \
					exec/utils/export_utils2.c


	


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