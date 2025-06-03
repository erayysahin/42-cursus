CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

NAME = ex01

SRCS = main.cpp Span.cpp

all: $(NAME)

$(NAME): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(NAME)

clean:
	@rm -f $(NAME)

fclean: clean

re: fclean all
