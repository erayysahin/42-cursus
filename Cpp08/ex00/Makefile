CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = ex00

SRCS = main.cpp

all: $(NAME)

$(NAME): $(SRCS) easyfind.hpp
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)

clean:
	@rm -f $(NAME)

fclean: clean

re: fclean all
.PHONY: all clean fclean re