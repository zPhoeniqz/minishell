NAME		 = minishell

INC_DIR		= inc
LIB_DIR		= lib
SRC_DIR		= src
BUILD_DIR	= build

LIBFT_DIR	= $(LIB_DIR)/libft
LIB_FT		= $(LIBFT_DIR)/libft.a

VPATH		= src:src
SRC			= main.c pipex_main.c pipex.c
OBJ			= $(addprefix $(BUILD_DIR)/,$(SRC:.c=.o))

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I$(INC_DIR) -I$(LIBFT_DIR)
REMOVE		= rm -rf

all: $(NAME)

$(LIB_FT):
	make -C $(LIBFT_DIR)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $^ -o $@

$(NAME): $(OBJ) $(LIB_FT)
	$(CC) $(CFLAGS) $(OBJ) $(LIB_FT) -o $(NAME)

clean:
	$(REMOVE) $(BUILD_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(REMOVE) $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
