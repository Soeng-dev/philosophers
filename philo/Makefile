NAME = philo


# Files

SRC = ./philos/philo.c		\
	  ./utils/str_utils.c	\
	  ./utils/time_utils.c	\
	  ./main.c

OBJ = $(SRC:.c=.o)



# Compile

CC = gcc

CFLAGS = #-g -fsanitize=address#-Wall -Wextra -Werror 

all : $(NAME)

$(NAME) : $(OBJ)

		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)



# Clean, Re

RM : rm -f

clean : 
		$(RM) $(OBJ)

fclean : clean
		$(RM) $(NAME)

re : fclean all
