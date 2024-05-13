NAME = minishell

SRC = main.c syntax.c utils_syntax.c ft_split.c 

OBJ = $(SRC:.c=.o)

HEADER = minishell.h

CC = cc

FLAG = -Wall -Werror -Wextra -lreadline

all: $(NAME)

%.o: %.c $(HEADER)
	$(CC) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) -g $(FLAG) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all