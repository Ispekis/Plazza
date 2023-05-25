##
## EPITECH PROJECT, 2023
## B-CCP-400-PAR-4-1-theplazza-joseph.yu
## File description:
## Makefile
##

TEST_FILES = tests/test_project.cpp

NAME = plazza

TEST_NAME = unit_tests

MAIN_SRC = src/main.cpp

SRC	=	src/Parsing.cpp			\
		src/Error.cpp			\
		src/Reception.cpp		\
		src/ErrorHandling.cpp	\
		src/Order.cpp			\
		src/Kitchen.cpp			\
		src/Ingredient.cpp			\
		src/Mythread.cpp			\
		src/Process.cpp			\
		src/Cook.cpp				\
		src/MessageQueue.cpp

SRC +=	src/Pizza/Pizza.cpp			\
		src/Pizza/Regina.cpp		\
		src/Pizza/Americana.cpp		\
		src/Pizza/Fantasia.cpp		\
		src/Pizza/Margarita.cpp		\

ALL_SRC += $(SRC)

ALL_SRC += $(MAIN_SRC)

OBJ	= $(ALL_SRC:.cpp=.o)

CFLAGS += -Wall -Wextra

CPPFLAGS += -I./include/

LDFLAGS += -lpthread

all: $(NAME)

# $(NAME): OBJ += $(MAIN_SRC:.cpp=.o)
$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS)

tests_run: clean
	$(CXX) $(SRC) $(TEST_FILES) $(CPPFLAGS) $(LDFLAGS) $(CFLAGS) -o $(TEST_NAME) -lcriterion --coverage
	./${TEST_NAME}
	gcovr --exclude tests/
	gcovr --exclude tests/ --branches

clean:
	$(RM) -f $(OBJ)
	$(RM) *.gcda
	$(RM) *.gcno

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

debug: CPPFLAGS += -g3
debug: re

.PHONY: all clean fclean re