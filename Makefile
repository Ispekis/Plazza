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

FILE_OBJ	= $(FILE:.cpp=.o)

all: $(NAME)

$(NAME): $(FILE_OBJ)
	$(CC) -o $(NAME) $(FILE_OBJ)

clean:
	$(RM) -f $(FILE_OBJ)

fclean: clean
	$(RM) -f $(NAME)

re: fclean re

.PHONY: all clean fclean re