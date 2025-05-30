#include "commands.hpp"
#include <stdexcept> 
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>

void CommandHandler::handleKick(server &server, std::string &line, int userIndex)
{
    std::istringstream ss(line);
    std::string chanName, targetNick, comment;
    ss >> chanName >> targetNick;
    std::getline(ss, comment);

    Client &me = server.users[userIndex];
    const std::string &meNick = me.getNickname();

    if (chanName.empty() || targetNick.empty())
        throw std::runtime_error(": 461 " + meNick + " KICK :Not enough parameters\r\n");

    Channel &ch = server.getChannel(chanName);

    bool isCreator = (ch.getCreator() == meNick);
    bool isOp      = ch.isOperator(meNick);
    bool targetIsCreator = (targetNick == ch.getCreator());
    bool targetIsOp      = ch.isOperator(targetNick);

    if (!isCreator && !isOp)
        throw std::runtime_error(": 482 " + meNick + " " + chanName + " :You're not channel operator\r\n");

    if (isOp && !isCreator)
    {
        if (targetIsCreator)
            throw std::runtime_error(": 482 " + meNick + " " + chanName + " :Cannot kick channel creator\r\n");
        if (targetIsOp)
            throw std::runtime_error(": 482 " + meNick + " " + chanName + " :Cannot kick channel operator\r\n");
    }

    if (!ch.isUser(targetNick))
        throw std::runtime_error(": 441 " + meNick + " " + targetNick + " :They aren't on that channel\r\n");

    std::string kickMsg = ":" + meNick + " KICK " + chanName + " " + targetNick;
    if (!comment.empty())
        kickMsg += " :" + comment;
    kickMsg += "\r\n";

    const std::vector<std::string> users = ch.getUsers();
    for (std::vector<std::string>::size_type idx = 0; idx < users.size(); ++idx)
    {
        Client &c = server.getClientByNick(users[idx]);
        send(c.getFd(), kickMsg.c_str(), kickMsg.size(), 0);
    }

    if (ch.isOperator(targetNick))
        ch.rmvChannelOperator(targetNick);
    ch.removeUser(targetNick);
}
