NAME = philo
FT = *.c

all : $(NAME)

$(NAME) :
	@gcc -Wall -Wextra -Werror $(FT) -o $(NAME)

clean :
	@rm -rf *.o *.dSYM

fclean : clean
	@rm -rf $(NAME)

re : fclean all 