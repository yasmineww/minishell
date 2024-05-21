NAME = minishell

SRC = main.c syntax.c utils_syntax.c ft_split.c ft_split_spaces.c quote_syntax.c \
	split_cmd.c add_space.c to_delete_env.c parsing.c expanding.c expanding_utils.c

OBJ = $(SRC:.c=.o)

HEADER = minishell.h

CC = cc

FLAG = -Wall -Wextra -Werror -g 

all: $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(FLAG) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) -lreadline $(FLAG) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all