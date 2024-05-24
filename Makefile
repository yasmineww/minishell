NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

SRCS =	main.c \
		execution/src/envp.c \
		execution/src/builtins.c \
		execution/src/cd.c \
		execution/src/pwd.c \
		execution/src/env.c \
		execution/src/echo.c \
		execution/src/execution.c \
		execution/src/unset.c \
		execution/src/export.c \
		execution/src/exporthelp.c \
		execution/src/redir.c \
		execution/src/utils.c \
		execution/utils/utils1.c \
		execution/utils/utils2.c \
		execution/utils/utils3.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c minishell.h utils/utils.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) -lreadline $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	  $(RM) $(OBJS)

fclean: 	clean
			$(RM) $(NAME)

re: 		fclean all

.PHONY:  clean fclean re all
