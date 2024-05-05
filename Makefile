NAME = minishell

SRC = file.c

OBJ = $(SRC:.c=.o)

HEADER = minishell.h

FLAG = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c $(HEADER)
	cc $(FLAG) -c $< -o $@

$(NAME): $(OBJ)
	cc $(FLAG) $(NAME) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all