NAME = minishell

SRC = main.c syntax.c utils_syntax.c ft_split.c store_cmd.c quote_syntax.c

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