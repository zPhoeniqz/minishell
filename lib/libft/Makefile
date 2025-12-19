BONUS_SRC := ./ft_calloc.c ./ft_lstadd_front_bonus.c ./ft_lstiter_bonus.c ./ft_lstnew_bonus.c ./ft_strchr.c ./ft_strjoin.c ./ft_strlen.c ./ft_strnstr.c ./ft_substr.c ./ft_toupper.c ./ft_mem.c ./ft_put.c ./ft_strconv.c ./ft_lstadd_back_bonus.c ./ft_lstdelone_bonus.c ./ft_lstmap_bonus.c ./ft_split.c ./ft_strdup.c ./ft_strlcat.c ./ft_strmapi.c ./ft_strrchr.c ./ft_ascii.c ./ft_bzero.c ./ft_lstclear_bonus.c ./ft_lstlast_bonus.c ./ft_lstsize_bonus.c ./ft_striteri.c ./ft_strlcpy.c ./ft_strncmp.c ./ft_strtrim.c ./ft_tolower.c
BONUS_SRC += ./ft_printf/ft_printf.c ./ft_printf/ft_utoa.c
BONUS_OBJ := $(BONUS_SRC:.c=.o)
SRC := $(filter-out %_bonus.c, $(BONUS_SRC))
OBJ := $(SRC:.c=.o)

NAME := libft.a

CC := cc
CFLAGS := -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

bonus: $(BONUS_OBJ)
	ar rcs $(NAME) $^

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BONUS_OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
