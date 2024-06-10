NAME = minishell

SRC = main.c \
	parsing/syntax.c parsing/utils_syntax.c parsing/ft_split.c parsing/ft_split_spaces.c parsing/quote_syntax.c \
	parsing/split_cmd.c parsing/add_space.c parsing/parsing.c parsing/expanding.c parsing/expanding_utils.c \
	parsing/handle_heredoc.c parsing/heredoc_utils.c \
  	execution/src/envp.c execution/src/builtins.c	execution/src/cd.c execution/src/pwd.c execution/src/env.c execution/src/echo.c \
  	execution/src/execution.c execution/src/unset.c execution/src/export.c execution/src/exporthelp.c execution/src/redir.c \
  	execution/src/utils.c execution/utils/utils1.c execution/utils/utils2.c	execution/utils/utils3.c \

OBJ = $(addprefix obj/, $(SRC:.c=.o))

HEADER = minishell.h

CC = cc

FLAG = -Wall -Wextra -Werror -g

all: $(NAME)

obj/%.o: %.c $(HEADER)
	@mkdir -p $(dir $@)
	@($(CC) $(FLAG) -c $< -o $@)
	@printf "\rcompiling...\033[K"

$(NAME): $(OBJ)
	@($(CC) -lreadline $(FLAG) $(OBJ) -o $(NAME))
	@printf "\r\033[K\033[33mminishell compiled\033[0m\n"

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all
