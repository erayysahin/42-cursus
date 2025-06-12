NAME    = bureaucracy
CC      = c++
CFLAGS  = -Wall -Wextra -Werror -std=c++98
SRCS    = Bureaucrat.cpp AForm.cpp ShrubberyCreationForm.cpp RobotomyRequestForm.cpp PresidentialPardonForm.cpp Intern.cpp main.cpp
OBJS    = $(SRCS:.cpp=.o)

all: $(NAME)

%.o: %.cpp
$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
rm -f $(OBJS)

fclean: clean
rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re