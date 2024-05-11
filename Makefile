NAME = minishell

SRC = parsing/main.c parsing/syntax.c parsing/utils_syntax.c
	execution/src/main.c execution/src/envp.c execution/src/utils.c execution/src/cd.c execution/src/pwd.c \
	execution/src/env.c execution/src/echo.c execution/utils/utils1.c execution/utils/utils2.c \

OBJ = $(SRC:.c=.o)

HEADER = minishell.h execution/utils/utils.h

CC = cc

RM = rm -rf

FLAG = -Wall -Werror -Wextra -lreadline

%.o: %.c $(HEADER)
	$(CC) $(FLAG) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAG) $(OBJ) -o $(NAME)

clean:
	  $(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
