NAME		= minishell

INC_DIR		= inc
SRC_DIR		= src
BUILD_DIR	= build

LIBFT_DIR	= libft
LIBFT_A		= libft/libft.a

VPATH		= src:tests
SRC			= builtins.c builtins_export.c builtins_utils.c exec_builtin.c exec.c exec_child.c exec_heredoc2.c exec_heredoc.c exec_path.c exec_pipe.c exec_redir.c exec_single.c exec_stage.c expansion.c ft_setenv.c gnl.c main.c parser.c path.c prompt.c signals.c token.c token_utils.c utils2.c utils.c
OBJ			= $(addprefix $(BUILD_DIR)/,$(SRC:.c=.o))

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -ggdb
REMOVE		= rm -rf

LIBFLAGS 	= -lreadline


all: $(NAME)

init_submodules:
	@git submodule update --init --recursive

$(LIBFT_A): | init_submodules
	@make -C $(LIBFT_DIR)

$(BUILD_DIR):
	@mkdir -p $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR) init_submodules
	@$(CC) $(CFLAGS) -c $^ -o $@

$(NAME): $(OBJ) $(LIBFT_A)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) $(LIBFLAGS) -o $(NAME)

clean:
	@$(REMOVE) $(BUILD_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@$(REMOVE) $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --suppressions=ignore_readline_errors.supp --suppressions=ignore_usr_bin.supp ./$(NAME)

.PHONY: all clean fclean re
