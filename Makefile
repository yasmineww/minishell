NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

SRCS =	src/main.c \
		src/envp.c \
		src/utils.c \
		src/cd.c \
		src/pwd.c \
		src/env.c \
		src/echo.c \
		utils/utils1.c \
		utils/utils2.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c minishell.h utils/utils.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC)-lreadline $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	  $(RM) $(OBJS)

fclean: 	clean
			$(RM) $(NAME)

re: 		fclean all

.PHONY:  clean fclean re all
