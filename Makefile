NAME = minishell

SRC = main.c \
	parsing/syntax.c parsing/utils_syntax.c parsing/ft_split.c parsing/ft_split_spaces.c parsing/quote_syntax.c \
	parsing/split_cmd.c parsing/add_space.c parsing/to_delete_env.c parsing/parsing.c parsing/expanding.c parsing/expanding_utils.c \
	parsing/handle_heredoc.c parsing/heredoc_utils.c \

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