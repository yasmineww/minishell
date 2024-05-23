NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

SRCS =	src/main.c \
		src/envp.c \
		src/builtins.c \
		src/cd.c \
		src/pwd.c \
		src/env.c \
		src/echo.c \
		src/execution.c \
		src/unset.c \
		src/export.c \
		src/exporthelp.c \
		src/redir.c \
		src/utils.c \
		utils/utils1.c \
		utils/utils2.c \
		utils/utils3.c \

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
