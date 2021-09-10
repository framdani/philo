CC= gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address

SRCS = srcs/main.c\
		srcs/init.c\
		srcs/time.c\
		srcs/check_args.c\
		srcs/actions.c\
		srcs/exit.c

NAME = philo

all:$(NAME)
$(NAME):$(SRCS)
	@$(CC) $(CFLAGS) $(SRCS) -o philo
	@echo "philo created successefully"

clean:
	@echo "There are no object files in this project"
fclean:clean
	@rm -rf philo
	@echo "remove executable"
re: fclean all
