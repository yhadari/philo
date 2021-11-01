NAME = philo
S = #-g -fsanitize=address
FT = *.c

all : $(NAME)

$(NAME) :
	@clear
	@gcc $(S) -Wall -Wextra -Werror $(FT) -o $(NAME)

clean :
	@rm -rf *.o *.dSYM

fclean : clean
	@rm -rf $(NAME)

re : fclean all 