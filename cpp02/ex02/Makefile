NAME    = fixedPoint
SRC     = Fixed.cpp main.cpp
OBJ     = $(SRC:.cpp=.o)

RM      = rm -rf
CC      = c++
FLAGS   = -Wall -Wextra -Werror -std=c++98

%.o: %.cpp
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re