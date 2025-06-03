CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = ex01
SRCS = main.cpp
HDR = iter.hpp

all: $(NAME)

$(NAME): $(SRCS) $(HDR)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all
.PHONY: all clean fclean re