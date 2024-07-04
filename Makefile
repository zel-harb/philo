CC = cc
FLAGS = -Wall -Wextra -Werror
NAME =philo
SRC = main.c \
	check_input.c \
	function_help.c 
OBJ = $(SRC:.c=.o)

all : $(NAME)
$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)
clean :
	rm -rf $(OBJ)
fclean : clean
	rm -rf $(NAME)
re : fclean all
