NAME = minishell
NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

SRCS =	src/main.c \
		utils/utils1.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c minishell.h utils/utils.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	  $(RM) $(OBJS)

fclean: 	clean
			$(RM) $(NAME)

re: 		fclean all

.PHONY:  clean fclean re all
