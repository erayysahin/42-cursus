#include "commands.hpp"
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>

void CommandHandler::handlePing(server &server, std::vector<Client> &clients, const std::string &argument, int userIndex)
{
    Client &me = clients[userIndex];
    const std::string nick = me.getNickname();

    std::istringstream ss(argument);
    std::string token;
    ss >> token;

    if (token.empty())
        throw std::runtime_error(": 409 " + nick + " :No origin specified\r\n");

    std::string reply = "PONG " + server.getServername() + " " + token + "\r\n";

    send(me.getFd(), reply.c_str(), reply.size(), 0);
}
