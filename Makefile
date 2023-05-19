##
## EPITECH PROJECT, 2023
## B-CCP-400-PAR-4-1-theplazza-joseph.yu
## File description:
## Makefile
##

NAME = plazza

SRC	=	src/main.cpp			\
		src/Parsing.cpp			\
		src/Error.cpp			\
		src/Reception.cpp		\
		src/ErrorHandling.cpp	\
		src/Order.cpp

OBJ	= $(SRC:.cpp=.o)

CFLAGS += -Wall -Wextra

CPPFLAGS += -I./include/

LDFLAGS += -lpthread

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS)

clean:
	$(RM) -f $(OBJ)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

debug: CPPFLAGS += -g3
debug: re

.PHONY: all clean fclean re