CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = ex02

SRCS = main.cpp

all: $(NAME)

$(NAME): $(SRCS) MutantStack.hpp
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)

clean:
	@rm -f $(NAME)

fclean: clean

re: fclean all
