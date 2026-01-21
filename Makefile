NAME		= minishell

INC_DIR		= inc
SRC_DIR		= src
BUILD_DIR	= build

LIBFT_DIR	= libft
LIBFT_A		= libft/libft.a

VPATH		= src:src
SRC			= prompt.c path.c signals.c
OBJ			= $(addprefix $(BUILD_DIR)/,$(SRC:.c=.o))

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -ggdb
REMOVE		= rm -rf

LIBFLAGS 	= -lreadline

all: $(NAME)

init_submodules:
	git submodule update --init --recursive

$(LIBFT_A): | init_submodules
	make -C $(LIBFT_DIR)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR) init_submodules
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) $(LIBFLAGS) -o $(NAME)

clean:
	$(REMOVE) $(BUILD_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(REMOVE) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --suppressions=ignore_readline_errors.supp ./$(NAME)

.PHONY: all clean fclean re
