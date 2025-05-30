NAME = ircserv

SRC = main.cpp server.cpp commands/commands.cpp client/client.cpp commands/utils.cpp commands/join.cpp \
commands/part.cpp commands/kick.cpp commands/nick.cpp commands/pass.cpp commands/topic.cpp commands/user.cpp commands/bot.cpp   commands/mode.cpp channel/channel.cpp \
commands/invite.cpp commands/privmsg.cpp commands/quit.cpp commands/ping.cpp commands/register.cpp


CXX = c++

CXX_FLAGS = -Wall -Wextra -Werror -std=c++98 -g

OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXX_FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
