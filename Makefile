src = *.c
philo = philo
FLAGS = -Wall -Wextra -Werror -fsanitize=thread
CC = gcc

all : philo
	
$(philo): $(src)
	@$(CC) $(FLAGS) $(src) -o philo -lpthread
	@tput setaf 2; echo "PHILOSOPHERS IS READY"

clean :
	@rm -f philo
	@tput setaf 1; echo "CLEAN COMPLET"

fclean : clean

re: fclean all
