##
## EPITECH PROJECT, 2023
## B-CCP-400-PAR-4-1-theplazza-joseph.yu
## File description:
## Makefile
##

NAME = plazza

SRC	=	src/main.cpp	\
		src/SafeQueue.cpp

OBJ	= $(SRC:.cpp=.o)

CFLAGS = -Wall -Wextra

CPPFLAGS = -iquote ./include/

LDFLAGS = -lpthread

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CPPFLAGS) $(LDFLAGS)

clean:
	$(RM) -f $(OBJ)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

.PHONY: all clean fclean re