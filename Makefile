SRCS =	./checks.c \
./philo_life.c \
./philo.c \
./set_args.c \
./utils.c \

NAME = philo
CFLAGS =  -Wall -Wextra -Werror
RM = rm -rf

all: ${NAME}

$(NAME): $(SRCS)
	@gcc $(CFLAGS) $(SRCS) -o $(NAME)
	@echo "-*-*-*-*-OK-*-*-*-*-"

clean:

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re 

# faruktinaz