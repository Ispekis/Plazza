##
## EPITECH PROJECT, 2023
## B-CCP-400-PAR-4-1-theplazza-joseph.yu
## File description:
## Makefile
##

NAME = plazza

CC = g++

SRC	=	src

FILE	=	$(SRC)/main.cpp	\
			$(SRC)/bootstrap.cpp	\
			$(SRC)/Parsing.cpp	\
			$(SRC)/Error.cpp	\
			$(SRC)/Plazza.cpp	\

FILE_OBJ	= $(FILE:.cpp=.o)

CPPFLAGS += -Wall -Wextra

CPPFLAGS += -iquote include/ -g3

LDFLAGS += -lpthread

all: $(NAME)

$(NAME): $(FILE_OBJ)
	$(CC) -o $(NAME) $(FILE_OBJ) $(CPPFLAGS) $(LDFLAGS)

clean:
	$(RM) -f $(FILE_OBJ)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

.PHONY: all clean fclean re