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
	@cd srcs && rm -rf main.o
	@cd srcs && rm -rf init.o
	@cd srcs && rm -rf time.o
	@cd srcs && rm -rf check_args.o
	@cd srcs && rm -rf actions.o
	@cd srcs && rm -rf exit.o
	@echo "remove obj files if exist"
fclean:clean
	@rm -rf philo
	@echo "remove executable"
re: fclean all
